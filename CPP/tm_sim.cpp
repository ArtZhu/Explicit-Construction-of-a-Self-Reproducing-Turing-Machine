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
#define TAPE_SIZE 20000000
#define DEBUG 1
char buffer[BUF_SIZE];
list<void *> freelist;

//Turing machine simulation
void runtm(char *filename, int verbose, int bidirectional, int showmap);
void read_transition_table(FILE *fp, int showmap);
void printconfig();
void nextconfig();

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
	char tape[TAPE_SIZE];
	char *start;
	char *end;
	char *current;
	int state;
} *Config;

struct _config _c;
Config config = &_c;
int prev_state = 0;
//state then symbol
map<int, map<char, int*> > table;

//def nextconfig(table, present_config):
void nextconfig(){
	char symbol;
	int *new_config;
	int newstate;
	char newsymbol;
	int direction;
	char *newcurrent, *newstart, *newend;
	//(tape,start,end,current,state)=present_config
	//symbol=tape[current]
	symbol = *config->current;
	//if (state,symbol) in table:
	new_config = table[config->state][symbol];
	if(new_config != NULL){
		//(newstate,newsymbol,direction)=table[(state,symbol)]
		newstate = *(new_config + 0);
		newsymbol = *(new_config + 1);
		direction = *(new_config + 2);

		//tape[current]=newsymbol
		//config->tape[config->current] = newsymbol;
		*config->current = newsymbol;
		//newcurrent=max(current+direction,0)
		//cout << (config->current == config->start) << endl;
		newcurrent = config->current+direction > config->tape ? config->current + direction : config->tape;
		//if current<start and tape[current] != ' ':
		if(config->current < config->start && newsymbol != ' '){
			// newstart=current
			newstart = config->current;
		}
		//else:
		else{
			//newstart=start
			newstart = config->start;
		}
		//if current>end and tape[current]!=' ':
		if(config->current > config->end && ((char) newsymbol ) != ' '){
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
		if(config->state >= 0){
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

	prev_state = config->state;
	config->start = newstart;
	config->end = newend;
	config->current = newcurrent;
	config->state = newstate;
}

//#pretty-print a configuration

//def printconfig(config):
void printconfig(){
	char *lowindex, *highindex, *p;
	//tape=config[0]
	//lowindex=min(config[1],config[3])
	lowindex = config->start < config->current? config->start:config->current;
	//highindex=max(config[2]+1,config[3]+1)
	highindex = config->end > config->current? config->end+1:config->current+1;
	//print 'state:',config[4]
	cout << "state:" << config->state << endl;
	//for j in range(lowindex,highindex):
	for(p=lowindex; p<highindex; p++){
		//if tape[j]==' ':
		if(*p == ' '){
			//print 'B',
			cout << 'B';
		}
		//else:
		else{
			//print tape[j],
			cout << *p;
		}
	}
	//print
	cout << endl;
	//for j in range(lowindex,highindex):
	for(p=lowindex; p<highindex; p++){
		//if config[3]==j:
		if(config->current == p){
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
void read_transition_table(FILE *fp, int showmap){
	//f=open(filename+'.tm','r')
	char c;
	int count=0;

	int state, newstate, direction;
	char symbol, newsymbol, dir;

	while(1){
		if((c = fgetc(fp)) == '#'){
			while((c = fgetc(fp)) != '\n') {}
		}
		else{
			ungetc(c, fp);
			goto label1;
		}
	}

label1:

	while(fscanf(fp, "%d %c %d %c %c\n", &state, &symbol, &newstate, &newsymbol, &dir)){
		direction = dir == 'R'? 1:-1;

		int *list = (int *) malloc(3 * sizeof(int));
		list[0] = newstate;
		list[1] = (int) newsymbol;
		list[2] = direction;
		table[state][symbol] = list;
		freelist.push_back(list);

		if(showmap) 
			cout << state << ";" << symbol << ";" << newstate << ";" << newsymbol << ";" << direction << endl;

		int _old, _new;
		_old = (symbol == 'B');
		_new = (newsymbol == 'B');

		if(_old)
			table[state][' '] = list;
		/*
		if(_new){
			newsymbol = ' ';
			list = (int*) malloc(3 * sizeof(int));
			list[0] = newstate;
			list[1] = (int) newsymbol;
			list[2] = direction;
			table[state][' '] = list;
			table[state]['B'] = list;
		}
		*/

		int done = 0;
		while(!done){
			if((c = fgetc(fp)) == '#'){
				while(fgetc(fp) != '\n') {}
			}
			else{
				if(c < 0)
					return;
				ungetc(c, fp);
				done = 1;
			}
		}
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
void runtm(char *filename, int verbose, int bidirectional, int showmap){
	FILE *fp;
	string input;
	list<string> inputstring;
	int inputstring_len;
	int j, count;
	char c;
	char *p;
	//d=read_transition_table(filename)
	fp = fopen(strcat(filename, ".tm"), "r");

	//if bidirectional:

	if(bidirectional){
		//## increase size
		//table=[' ']*100000+list(inputstring)+[' ']*100000
		for(p=config->tape; p<config->tape + TAPE_SIZE; p++)
			*p = ' ';

		//config=(table,100000,100000+len(inputstring)-1,100000,1000)
		config->start = config->tape + TAPE_SIZE/2;
		//config->end = 1000000 + inputstring_len - 1;
		config->current = config->start;
	}
	//else:
	else{
		cout << "only bidirectional mode implemented" << endl;
		//table=list(inputstring)+[' ']*200000
		exit(0);
	}
	//put input string
	// config -> end
	// config -> state
	p = config->start;
	while((c = fgetc(fp)) != '~'){
		if(c == '\n')
			c = ' ';

		*p = c;
		p++;
	}
	config->end = p;
	// '\n'
	fgetc(fp);
	fscanf(fp, "%d\n", &(config->state));
	// '\n'
	fscanf(fp, "%c\n", &c);
	//cout << "scanned:" << c << endl;

	//cout << (c = fgetc(fp)) << endl;
	//ungetc(c, fp);

	read_transition_table(fp, showmap);

	fclose(fp);
	count = 0;
	//print count+1,'.',
	cout << count+1 << '.';
	//printconfig(config)
	printconfig();
	//while config[4]>=0:
	while(config->state >= 0){
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
		if(config->state<0){
			//if config[4]==-1:
			switch(config->state){
				case -1:
					cout << "accept" << endl;
					break;
				case -2:
					cout << "reject" << endl;
					break;
				default:
					// -3
					cout << "halt" << endl;
					break;
			}
				//print 'accept'
			//elif config[4]==-2:
				//print 'reject'
			//else:
				//print 'halt'

			//print count+1,'steps'
			cout << count+1 << "steps" << endl;
			cout << "from state: " << prev_state << endl;
			//for j in range(config[1],config[2]+1):
			int ready = 0;
			for(p=config->start; p<config->end+1; p++){
				//print config[0][j],
				if(!ready){
					if(*p != 'B' && *p != ' ')
						ready = 1;
				}

				if(ready){
					if(*p == 'B')
						cout << ' ';
					else
						cout << *p;
				}
			}
			//print
			cout << endl;
		}
	}
}


int main(int argc, char ** argv){
	char *filename;
	int verbose, bidirectional, showmap;
	int j;

	filename = argv[1];
	verbose = 0;
	bidirectional = 1;
	showmap = 0;

	for(j=2; j<argc; j++){
		if(!strcmp(argv[j], "V"))
			verbose = 1;
		if(!strcmp(argv[j], "NoB"))
			bidirectional = 0;
		if(!strcmp(argv[j], "T"))
			showmap = 1;
	}
	runtm(filename, verbose, bidirectional, showmap);

	return 0;
}
