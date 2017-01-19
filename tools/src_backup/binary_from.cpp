/*	file: binary_from.cpp
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
const char LR_STRING[] = "LR";
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
		v = line.substr(0, index);
		k = line.substr(index+1);
		if(DEBUG)
			cout << "key:" << k << ":value:" << v << endl;
		tape_symbol[k] = v;
		line = "";
	}

label1:
	in.close();


	string piece;

	in_name = base_file_name + ".enc";
	out_name = base_file_name + ".dec";

	cout << "-------------------" << endl;
	cout << "in_name " << in_name << endl;
	cout << "out_name " << out_name << endl;

	in.open(in_name);
	out.open(out_name);

	//
	int j=-1;
	while(!in.eof()){
		if(DEBUG)
			cout << "-------------------" << endl;
		while(++j < 5){
			piece = "";
			while((c=in.get()) != '\n'){
				if(c<0)
					goto label2;
				piece += c;
				if(piece.length() > s.length())
					if(!piece.substr(piece.length() - s.length()).compare(s)){
						//cout << "substring" << piece.substr(piece.length() - s.length()) << endl;
						piece = piece.substr(0, piece.length() - 1);
						break;
					}
			}
			if(DEBUG)
				cout << "index=" << j << ";piece=" << piece << endl;
			spec[j] = "";
			spec[j] += piece;
			piece = "";
		}

		string TS0, TS1;
		map<string, string>::iterator it = tape_symbol.find(*ts0);
		if(it != tape_symbol.end())
			TS0 = tape_symbol[*ts0];
		else
			TS0 = convert_from(*ts0, -8);
		it = tape_symbol.find(*ts1);
		if(tape_symbol.find(*ts1) != tape_symbol.end())
			TS1 = tape_symbol[*ts1];
		else
			TS1 = convert_from(*ts1, -8);

		if(DEBUG)
			cout << "TS0:" << TS0 << "; TS1:" << TS1 << endl;

		cout << "q0:" << *q0 << "; q1:" << *q1 << endl;
		string Q1 = convert_from(*q1, -8);
		cout << "Q1 original:" << Q1 << endl;
		if(tape_symbol.find(*q1) != tape_symbol.end()){
			Q1 = tape_symbol[*q1];
		}
		out << convert_from(*q0, -8) << " " << TS0 << " " << Q1 << " " << TS1 << " " << tape_symbol[*dir] << endl;
		if(DEBUG)
			cout << convert_from(*q0, -8) << " " << TS0 << " " << Q1 << " " << TS1 << " " << tape_symbol[*dir] << endl;
		j=-1;
	}
label2:

	in.close();
	out.flush();
	out.close();


	cout << "-------------------" << endl;
	return 0;
}
