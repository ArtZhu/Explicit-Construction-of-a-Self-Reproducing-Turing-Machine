/* 	file: 	Q.cpp
 *	author: Tiane Zhu
 *	date:		Apr 29, 2016
 *
 */

#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char **argv)
{
	ifstream in;
	ofstream out;
	string in_name, out_name;
	size_t index;
	char c;
	
	in_name = argv[1];
	//start_state
	int i = atoi(argv[2]);

	index = in_name.find_last_of(".");
	out_name = in_name.substr(0, index) + ".q";

	in.open(in_name);
	out.open(out_name);

	while((c=in.get()) != '\n'){
			if(c == ' ')
				c = 'B';
			if(c < 0)
				goto label1;
			out << i << " B " << i+1 << " " << c << " " << "R" << endl;
			i++;
	}
	label1:

	out.flush();
	in.close();
	out.close();
}
