/* file: round.cpp
 * author: Tiane Zhu
 * date: May 2, 2016
 *
 * round up output from turing machine simluator
 */

#define DEBUG 1

#include<fstream>
using namespace std;

int main(){
	char c;
	int i;
	string line="";
	int start, flag;

	string file_name = "out";

	start=i=flag=0;
	while((c=getchar()) != EOF){
		if(c == '\n'){
			i++;
		}
		else{
			if(i==5){
				if(!start){
				if(c != ' ')
					start = 1;
					line += c;
				}else{
					if(flag){
						flag=0;
						line += c;
					}else{
						flag=1;
					}
				}
			}
		}
	}

	ofstream out;
	out.open(file_name);

	out << line;
	out.flush();
	out.close();

	return 0;
}
