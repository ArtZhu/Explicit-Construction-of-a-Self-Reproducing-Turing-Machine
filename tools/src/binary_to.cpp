/*	file: binary_to.cpp
 *	author: Tiane Zhu
 *	date: 	Apr 29th, 2016
 */
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<string.h>
#include"states_convert.h"

#define DEBUG 1

const char TAPE_SYMBOL_STRING[] = "tape_symbol";
const char SEPARATOR_STRING[] = "separator";

using namespace std;

int main(int argc, char** argv){
	ifstream in;
	ofstream out;
	string in_name, out_name;
	string base_file_name(argv[1]);
	size_t index;

	char c;
	int mult_line;
	map<string, string> tape_symbol;
	string k = "", v = "";
	string line = "";

	string spec[5];
	string *q0, *ts0, *q1, *ts1, *dir, s;
	q0 = &(spec[0]);
	ts0 = &(spec[1]);
	q1 = &(spec[2]);
	ts1 = &(spec[3]);
	dir = &(spec[4]);

	if(!strcmp(argv[argc-1], "mult")){
		if(DEBUG){
			cout << "------------------" << endl;
			cout << "mult line" << endl;
			cout << "------------------" << endl;
			}
		mult_line = 1;
	}else{
		if(DEBUG){
			cout << "------------------" << endl;
			cout << "1 line" << endl;
			cout << "------------------" << endl;
			}
		mult_line = 0;
	}

	
	//encoding scheme
	in.open(base_file_name + ".scheme");
	while(!in.eof()){
		while((c = in.get()) != '\n'){
			if(c < 0)
				goto label1;
			line += c;
		}
		if(!line.compare(TAPE_SYMBOL_STRING)){
			line = "";
			if(DEBUG){
				cout << "------------------" << endl;
				cout << "TAPE_SYMBOL_AND_LR_MAP:" << endl;
				}
			continue;
		}
		if(!line.compare(SEPARATOR_STRING)){
			line = "";
			while((c = in.get()) != '\n')
				line += c;

			s = "";
			s += line;
			line = "";
			if(DEBUG){
				cout << "------------------" << endl;
				cout << "separator:" << s << endl;
				}
			continue;
		}

		index = line.find_last_of(":");
		//cout << "index=" << index << endl;
		k = line.substr(0, index);
		v = line.substr(index+1);
		if(DEBUG)
			cout << "key:" << k << ":value:" << v << endl;
		tape_symbol[k] = v;
		line = "";
	}

label1:
	in.close();


	string piece;

	in_name = base_file_name + ".dec";
	out_name = base_file_name + ".enc";

	cout << "------------------" << endl;
	cout << "in_name " << in_name << endl;
	cout << "out_name " << out_name << endl;
	cout << "------------------" << endl;

	in.open(in_name);
	out.open(out_name);

	//
	int j=-1;
	int first = 0;
	while(!in.eof()){
		if(DEBUG)
			cout << "------------------" << endl;
		while((c=in.peek()) == '#' || c == '~'){
			while((c=in.get()) != '\n'){}
		}
		while(++j < 5){
			piece = "";
			while((c=in.get()) != ' ' && c != '\n'){
				if(c<0)
					goto label2;
				piece += c;
			}
			if(DEBUG)
				cout << "index=" << j << ";piece=" << piece << endl;
			spec[j] = "";
			spec[j] += piece;
			piece = "";
		}

		if(first++ && !mult_line)
			out << s;

		string TS0, TS1;
		if(DEBUG)
			cout << "*ts0:" << *ts0 << "; binary:" << convert_to(*ts0, 8) << endl;
		TS0 = convert_to(*ts0, 8);
		if(DEBUG)
			cout << "*ts1:" << *ts1 << "; binary:" << convert_to(*ts1, 8) << endl;
		TS1 = convert_to(*ts1, 8);
		if(DEBUG)
			cout << "TS0:" << TS0 << "; TS1:" << TS1 << endl;
		map<string, string>::iterator it = tape_symbol.find(*ts0);
		if(it != tape_symbol.end())
			TS0 = tape_symbol[*ts0];
		it = tape_symbol.find(*ts1);
		if(tape_symbol.find(*ts1) != tape_symbol.end())
			TS1 = tape_symbol[*ts1];

		if(DEBUG)
			cout << "TS0:" << TS0 << "; TS1:" << TS1 << endl;
		string Q1 = convert_to(*q1, 8);
		if((*q1).at(0) == '-')
			Q1 = tape_symbol[*q1];
		out << convert_to(*q0, 8) << s << TS0 << s << Q1 << s << TS1 << s << tape_symbol[*dir];
		if(mult_line)
			out << endl;
		if(DEBUG)
			cout << convert_to(*q0, 8) << s << TS0 << s << Q1 << s << TS1 << s << tape_symbol[*dir]<< endl;
		j=-1;
	}
label2:

	in.close();
	out.flush();
	out.close();

	return 0;
}
