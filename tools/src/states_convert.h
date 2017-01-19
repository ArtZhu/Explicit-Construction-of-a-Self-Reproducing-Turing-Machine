/* file: states_convert.h
 * Date: Apr 28, 2016
 */
#include<iostream>
#include<sstream>
#include<bitset>
using namespace std;

string convert_from(string binary, int offset){
	int i=1;
	unsigned long D = 0;
	string bit;
	while(binary.length() > 0){
		bit = binary.substr(binary.length()-1);
		if(!bit.compare("1")){
			D += i;
		}
		binary = binary.substr(0, binary.length()-1);
		i = i*2;
	}

	D += offset;
	stringstream ss;
	ss << D;
	return ss.str();
}

string convert_to(string decimal, int offset){
	stringstream ss;
	unsigned long D;
	ss.str(decimal);
	ss >> D;
	string ret = "";
	D += offset;
	while(D>0){
		if(D%2)
			ret = "1" + ret;
		else
			ret = "0" + ret;
		D = D/2;
	}
	return ret;
}

/*
string convert_to(string decimal){
	unsigned long D;
	ss.str(decimal)
	ss >> D;
	D += 8;
	int l = log2(D) + 1; 
	int *ptr = &l;
	D = bitset<*ptr>(l).to_ulong() - 8;
	return bitset<*ptr>(D).to_string(); //to binary
}
*/

/*
int main(int argc, char ** argv)
{
	std::string binary = std::bitset<7>(atoi(argv[1])).to_string(); //to binary
	std::cout<<binary<<"\n";

	unsigned long decimal = std::bitset<6>(binary).to_ulong();
	std::cout<<decimal<<"\n";
}
*/
