/*	file: binary_from.cpp
 *	author: Tiane Zhu
 *	date: 	Apr 20th, 2016
 */
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<string.h>
#include<stdlib.h>

#define DEBUG 0

const char STATE_STRING[] = "state";
const char TAPE_SYMBOL_STRING[] = "tape_symbol";
const char LR_STRING[] = "LR";
const char SEPARATOR_STRING[] = "separator";

using namespace std;

int main(int argc, char** argv){
	ifstream in;
	ofstream out;
	string in_name, out_name;
	size_t index;
	stringstream ss;

	char c;
	string line = "";

	string spec[5];
	string *q0, *ts0, *q1, *ts1, *dir, s;
	q0 = &(spec[0]);
	ts0 = &(spec[1]);
	q1 = &(spec[2]);
	ts1 = &(spec[3]);
	dir = &(spec[4]);

	int start_state = atoi(argv[2]);
	int Q0, Q1;

	int j=-1;
	in_name = argv[1];
	index = in_name.find_last_of(".");
	ss << ".connected" << start_state;
	out_name = in_name.substr(0, index) + ss.str();

	cout << "-------------------" << endl;
	cout << "in_name " << in_name << endl;
	cout << "out_name " << out_name << endl;
	cout << "-------------------" << endl;

	in.open(in_name);
	out.open(out_name);

	for(getline(in, line); line.size() > 1; getline(in, line)){
		if(line.at(0) == '#'){
			out << line << endl;
			continue;
		}
		*q0 = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
		*ts0 = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
		*q1 = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
		*ts1 = line.substr(0, line.find(" "));
		*dir = line.substr(line.find(" ") + 1);
		
		if(DEBUG)
			cout << *q0 << " " << *ts0 << " " << *q1 << " " << *ts1 << " " << *dir << endl;
		istringstream iss0;
		iss0.str(*q0);
		iss0 >> Q0;
		istringstream iss1;
		iss1.str(*q1);
		iss1 >> Q1;

		Q0 += start_state;
		Q1 += start_state;

		ss.str("");
		ss << Q0;
		*q0 = ss.str();
		ss.str("");
		ss << Q1;
		*q1 = ss.str();

		out << *q0 << " " << *ts0 << " " << *q1 << " " << *ts1 << " " << *dir << endl;
		if(DEBUG)
			cout << *q0 << " " << *ts0 << " " << *q1 << " " << *ts1 << " " << *dir << endl;
	}
	in.close();
	//

	in.close();
	out.flush();
	out.close();

	cout << "-------------------" << endl;
	return 0;
}
