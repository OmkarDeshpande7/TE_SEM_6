#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<fstream>
#include<string.h>
using namespace std;

struct keyword{
	string token;
	int arguments,opcode;
};


int main(){
	char ch;
	string word;
	struct keyword tokens[10] = {{"START",1,00},{"READ",1,00},{"MOVER",2,00},{"ADD",2,00},{"MOVEM",2,00},{"PRINT",1,00},{"STOP",-1		,00},{"END",-1,00}};
	int chars=0,words=0,sentences=0,count[10]={0,0,0,0,0,0,0,0,0,0};
	fstream new_file;
	new_file.open("test.asm",ios::in | ios::app); 
	
	while(!new_file.eof()){
	new_file.get(ch);
	if(ch == '\n'){
		++words;
		++sentences;
		}
	if(ch == ' ')
		++words;
	++chars;

	cout<<ch;
	}
	cout<<endl<<"There are "<<chars<<" chars, "<<words<<" words, and "<<sentences - 1<<" sentences !"<<endl;
	
	
	new_file.clear();
	new_file.seekg(0);
		
	while(new_file>>word){
	//cout<<word;
	int i,counter=-1;
	char ch1=' ';
	for(i=0;i<8;i++)
	if(word.find(tokens[i].token) != string::npos){
	count[i]++;
	while(new_file.get(ch1)){	
	if(ch1 == '\n'){
	break;
	}
	if(ch1==' ' || ch1==',')
	continue;
	counter++;
	}
	if (counter != tokens[i].arguments)
	cout<<tokens[i].token<<" has wrong no of arguments "<<counter<<"\n";
	break;
	}
	if(i==8)
	cout<<"word "<<word<<" not found"<<endl;
	
	
	}

	for(int i=0;i<8;i++)
	cout<<tokens[i].token<<" "<<count[i]<<endl;

	

	new_file.close();
}
