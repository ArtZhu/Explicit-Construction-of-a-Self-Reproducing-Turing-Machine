/* file: tm_sim.cpp
 * author: Tiane Zhu
 * date: May 4, 2016
 */

/*
 * aiming for a Turing Machine simulator with shorter running time
 *	Extension from Prof. Straubing's Turing Machine Simulator;
 */

//./tm_sim copy V NoB
//run copy.tm verbose + not bidirectional

#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
#include<map>
#include<list>
using namespace std;

#define BUF_SIZE 256
#define TAPE_SIZE 2000000
#define DEBUG 1
char buffer[BUF_SIZE];

//Turing machine simulation
void runtm(char *filename, int verbose, int bidirectional);
void read_transition_table(char *filename);
void printconfig();
void nextconfig();

string get(list<string> l, int index){
	list<string>::iterator it;
	it = l.begin();
	advance(it, index);
	return *it;
}
//Transition table is a dictionary of key-value pairs (q,c):(q',c',D) where
//D is -1 or 1, for left and right, tape symbols c, c' are characters,
//states q,q' are integers.

//Conventions: If a state,symbol pair is not in the dictionary,
// transition to reject state. 0 is intial state, -1 is accept and
//halt, -2 is reject and halt, -n with n>2 is halt without specifying
//decision.

//The tape is a list of 20000 chars.  The configuration is a tuple
/*											2000000																		*/
//of the tape, an index start giving the location of first nonblank symbol
//an index end giving the location of the last nonblank symbol
//an index current giving the location of the reading head, and the state.

//In bidirectional mode, the simulation will start at cell 10000, so in practice
/*																												 1000000*/
//it should never run off the end of the tape.

//In unidirectional mode, we start at 0.  The way the current position is updated
//keeps the reading head at 0 on a left move (the same happens in bidirectional
//mode, but this behavior will never be encountered in practice)

typedef struct _config{
	list<string> tape;
	int start;
	int end;
	int current;
	string state;
} *Config;

struct _config _c;
Config config = &_c;
//state then symbol
map<string, map<string, list<string> > > table;
map<string, int> d;

//def nextconfig(table, present_config):
void nextconfig(){
	string symbol;
	list<string> new_config;
	string newstate;
	string newsymbol, direction;
	int newcurrent, newstart, newend;
	//(tape,start,end,current,state)=present_config
	//symbol=tape[current]
	list<string>::iterator tape_it;
	tape_it = config->tape.begin();
	advance(tape_it, config->current);
	symbol = *tape_it;
	//if (state,symbol) in table:
	new_config = table[config->state][symbol];
	if(new_config.size() > 0){
		//(newstate,newsymbol,direction)=table[(state,symbol)]
		newstate = new_config.front();
		new_config.pop_front();
		newsymbol = new_config.front();
		direction = new_config.back();

		//tape[current]=newsymbol
		//config->tape[config->current] = newsymbol;
		*tape_it = newsymbol;
		//newcurrent=max(current+direction,0)
		newcurrent = config->current+d[direction] > 0 ? config->current + d[direction] : 0;
		//if current<start and tape[current] != ' ':
		if(config->current < config->start && *tape_it != " "){
			// newstart=current
			newstart = config->current;
		}
		//else:
		else{
			//newstart=start
			newstart = config->start;
		}
		//if current>end and tape[current]!=' ':
		if(config->current > config->end && *tape_it != " "){
			//newend=current
			newend = config->current;
		}
		//else:
		else{
			//newend=end
			newend = config->end;
		}
	}
	// elif state>=0:
	else{
		if(config->state[0] != '-'){
			//newstate=-2
			newstate = -2;
			//newcurrent=current
			newcurrent = config->current;
			//newstart=start
			newstart = config->start;
			//newend=end
			newend = config->end;
		}
		//else:
		else{
			//newstate=state
			newstate = config->state;
			//newcurrent=current
			newcurrent = config->current;
			//newstart=start
			newstart = config->start;
			//newend=end
			newend = config->end;
		}
	}
	//return (tape,newstart,newend,newcurrent,newstate)

	config->start = newstart;
	config->end = newend;
	config->current = newcurrent;
	config->state = newstate;
}

//#pretty-print a configuration

//def printconfig(config):
void printconfig(){
	int lowindex, highindex;
	int j;
	//tape=config[0]
	//lowindex=min(config[1],config[3])
	lowindex = config->start < config->current? config->start:config->current;
	//highindex=max(config[2]+1,config[3]+1)
	highindex = config->end > config->current? config->end+1:config->current+1;
	//print 'state:',config[4]
	cout << "state:" << config->state << endl;
	//for j in range(lowindex,highindex):
	for(j=lowindex; j<highindex; j++){
		//if tape[j]==' ':
		string tape_j = get(config->tape, j);
		if(tape_j.compare(" ") == 0){
			//print 'B',
			cout << 'B';
		}
		//else:
		else{
			//print tape[j],
			cout << tape_j;
		}
	}
	//print
	cout << endl;
	//for j in range(lowindex,highindex):
	for(j=lowindex; j<highindex; j++){
		//if config[3]==j:
		if(config->current == j){
			//print '^',
			cout << '^';
		}
		//else:
		else{
			//print ' ',
			cout << ' ';
		}
	}
	//print
	cout << endl;
}

//#read the transition table in from a specification file.
//#Conventions:  The filename is the second argument followed by '.tm'.  It
//#is assumed to be in the current directory.
//#Lines are formatted as
//#q a q' b' D
//#where q,q' are integers, a,b characters, and D is the character 'L' or 'R'
//#The initial state is always to be 0, accept, reject and halt -1,-2,-3.
//#The blank symbol is indicated by the character B,which must not be used as
//#a separate symbol of the tape alphabet.
//#Lines that start with the symbol # are treated as comments

//def read_transition_table(filename):
void read_transition_table(ifstream *in){
	//f=open(filename+'.tm','r')
	string line;
	char c;
	int count=0;

	line = "";

	int index = 0;
	string state, symbol, newstate, newsymbol, direction;

	(*in).get(c);
	while(1){
		while((*in).get(c)){
			//cout << c << endl;
			if(c == '\n' || c == ' ' || c == EOF)
				goto label1;
			char arr[2];
			arr[0] = c; arr[1] = '\0';
			line += string(arr);
		}
		label1:

		switch(index){
			case 0:
				state = line;
				line = "";
				index++;
				break;
			case 1:
				symbol = line;
				line = "";
				index++;
				break;
			case 2:
				newstate = line;
				line = "";
				index++;
				break;
			case 3:
				newsymbol = line;
				line = "";
				index++;
				break;
			case 4:
				direction = line;
				line = "";
				index = 0;
				break;
		}

		if(index == 0){
			list<string> s;
			s.push_back(newstate);
			s.push_back(newsymbol);
			s.push_back(direction);
			table[state][symbol] = s;

			//cout << state << ";" << symbol << ";" << newstate << ";" << newsymbol << ";" << direction << endl;

			int _old, _new;
			_old = symbol.compare("B");
			_new = newsymbol.compare("B");

			if(_old)
				table[state][" "] = s;
			if(_new){
				newsymbol = " ";
				list<string> s1;
				s1.push_back(newstate);
				s1.push_back(newsymbol);
				s1.push_back(direction);
				table[state][" "] = s1;
				table[state]["B"] = s1;
			}
		}

		//cout << c << endl;
		if((*in).peek() < 0)
			return;
	}

}

//d={}
//for line in f:
/*
	 e = in.getline(c);
	 seq=line.split()
#print seq
if (len(seq)>0) and (seq[0][0]!='#'):
_old=False;
_new=False;

state=int(seq[0])
sym=seq[1]
if sym=='B':
sym1=' '
_old=True
newstate=int(seq[2])
newsym=seq[3]
if newsym=='B':
newsym1=' '
_new=True
if seq[4]=='L':
direction=-1
else:
direction=1
d[(state,sym)]=(newstate,newsym,direction)
if _old:
d[(state,sym1)]=(newstate,newsym,direction)
if _new:
d[(state,sym)]=(newstate,newsym1,direction)
if _old and _new:
d[(state,sym1)]=(newstate,newsym1,direction)

return d
 */


//#Simulate the Turing machine specified in the filename on the input string
//#We don't let the simulation continue more than 1000 steps.  If you want,
//#you can modify the code so that it shuts up and does not print the
//#configuration at each step.

//def runtm(filename,inputstring,verbose=True,bidirectional=True):
void runtm(char *filename, int verbose, int bidirectional){
	string file_name = string(filename);
	string input;
	list<string> inputstring;
	int inputstring_len;
	int j, count;
	char c;
	//d=read_transition_table(filename)
	ifstream in;

	in.open(file_name + ".tm");
	inputstring_len = 0;
	for(in.get(c); c != 'Z'; in.get(c)){
		if(c == ' ' || c == '\n'){
			inputstring_len++;
			c = '~';
		}
		input += c;
	}

	//separate input;
	size_t index;
	int i;
	for(i=0; i<inputstring_len; i++){
		index = input.find_first_of('~');
		string s = input.substr(0, index);
		inputstring.push_back(s);
		input = input.substr(index + 1);
		if(i == inputstring_len - 1)
			inputstring.push_back(input);
	}

	read_transition_table(&in);

	in.close();
	//if bidirectional:

	if(bidirectional){
		//## increase size
		//table=[' ']*100000+list(inputstring)+[' ']*100000
		int i;
		for(i=0; i<TAPE_SIZE; i++){
			config->tape.push_back(" ");
		}
		list<string>::iterator it, tape_it;
		it = inputstring.begin();
		tape_it = config->tape.begin();
		//for(i=0; i<TAPE_SIZE/2; i++)
			//tape_it++;
		advance(tape_it, TAPE_SIZE/2);
		for(j=0; j<inputstring_len; j++){
			*tape_it = *it;
			it++;
			tape_it++;
		}
		//config=(table,100000,100000+len(inputstring)-1,100000,1000)
		config->start = 1000000;
		config->end = 1000000 + inputstring_len - 1;
		config->current = 1000000;
		config->state = "1000";
	}
	//else:
	else{
		//table=list(inputstring)+[' ']*200000
		for(i=0; i<TAPE_SIZE; i++){
			config->tape.push_back(" ");
		}
		list<string>::iterator it, tape_it;
		it = inputstring.begin();
		tape_it = config->tape.begin();
		for(j=0; j<inputstring_len; j++){
			*tape_it = *it;
			it++;
			tape_it++;
		}
		//config=(table,0,len(inputstring)-1,0,0)
		config->start = 0;
		config->end = inputstring_len - 1;
		config->current = 0;
		config->state = "1000";
	}
	count = 0;
	//print count+1,'.',
	cout << count+1 << '.';
	//printconfig(config)
	printconfig();
	//while config[4]>=0:
	while(config->state[0] != '-'){
		//count+=1
		count+=1;
		//config=nextconfig(d,config)
		nextconfig();
		//if verbose:
		if(verbose){
			//print count+1, '.',
			//printconfig(config)
			cout << count+1 << '.';
			printconfig();
		}
		//if config[4]<0:
		if(config->state[0] == '-'){
			//if config[4]==-1:
			if(config->state.compare("-1")){
				//print 'accept'
				cout << "accept" << endl;
			}
			//elif config[4]==-2:
			else{
				if(config->state.compare("-2")){
					//print 'reject'
					cout << "reject" << endl;
				}
				//else:
				else{
					//print 'halt'
					cout << "halt" << endl;
				}
				//print count+1,'steps'
				cout << count+1 << "steps" << endl;
				//for j in range(config[1],config[2]+1):
				for(j=config->start; j<config->end+1; j++){
					//print config[0][j],
					cout << get(config->tape, j);
				}
				//print
				cout << endl;
			}
		}
	}
}

int main(int argc, char ** argv){
	char *filename;
	string inputstring;
	int verbose, bidirectional;
	int j;

	filename = argv[1];
	verbose = 0;
	bidirectional = 1;

	for(j=2; j<argc; j++){
		cout << 1 << endl;
		if(strcmp(argv[j], "V"))
			verbose = 1;
		if(strcmp(argv[j], "NoB"))
			bidirectional = 0;
	}
	runtm(filename, verbose, bidirectional);

	return 0;
}
