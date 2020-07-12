#include<iostream>
#include<stdlib.h>
#include<string>
#include<stdio.h>
#include<string.h>
#include<fstream>
#define N 14
#define M 11
using namespace std;
fstream fin,fout;
int symcounter=0,litcounter=0;
struct keywords{
    string key,token; 
};
struct terminals{
    string ter,token;
};

struct symbols{
    string sym,token;
}symbol[20];

struct literals{
    string lit,token;
}literal[20];
bool isNumber(char x){
	if(x=='0' ||x=='1' ||x=='2' ||x=='3' ||x=='4' ||x=='5' ||x=='6' ||x=='7' ||x=='8' ||x=='9' )
		return true;
	return false;
}
void check_symbol(char * buffer){
    char str[20];
    str[0]='S';
    str[1]='\0';
    if(isNumber(buffer[1]))
    	{
    	cout<<"Illegal Identifier !\n";
    	return;
    	}
    symbol[symcounter].sym=buffer+1;
    strcat(str,to_string(symcounter+1).c_str());
    symbol[symcounter].token = str;
    cout<<"\t"<<symbol[symcounter].token<<"\t"<<symbol[symcounter].sym<<endl;
    symcounter++;
}

void check_literal(char *buffer){
    char str[20];
    str[0]='L';
    str[1]='\0';
    literal[litcounter].lit=buffer;
    strcat(str,to_string(litcounter+1).c_str());
    literal[litcounter].token = str;
    cout<<"\t"<<literal[litcounter].token<<"\t"<<buffer<<endl;
    litcounter++;
}
int main(){
    char current,next,buffer[50],temp;
    int i=0,j=0,l=0;
    keywords keyword[20]={{"int","K1"},{"char","K2"},{"float","K3"},{"auto","K4"},
                            {"do","K5"},{"while","K6"},{"for","K7"},{"struct","K8"},
                            {"if","K9"},{"continue","K10"},{"break","K11"}};
    terminals terminal[20]={{" ","T1"},{",","T2"},{"{","T3"},{"}","T4"},
                            {"(","T5"},{")","T6"},{";","T7"},{"[","T8"},
                            {"]","T9"},{"+","T10"},{"-","T11"},{"/","T12"},{"*","T13"},{"\n","T14"}};
    fin.open("input.c",ios::in);
    fout.open("output.txt",ios::out);
    fin.get(current);
    fin.seekg(1);
    cout<<"UNIFORM SYMBOL TABLE : \n";
    while(fin.get(next)){
		
        buffer[i++]=current;
        buffer[i]='\0';
        
        for(int k=0;k<N;k++){
        
            if(next==terminal[k].ter.c_str()[0]){
                
                for(j=0;j<M;j++){
                    if(!strcmp(keyword[j].key.c_str(),buffer)){
                        cout<<"\t"<<keyword[j].token<<"\t"<<buffer<<endl;
                        break;
                        }
                    
                    }
                    if(j==M){
                        for(l=0;l<N;l++){
                            if(current==terminal[l].ter.c_str()[0])
                            	{
                            	if(current==' ')
                            		continue;
                            	if(next=='+' && current=='+')
                            	{
                            		cout<<"\t"<<"O1"<<"\t++"<<endl;
                            		continue;
                            	}
                            	if(next=='+' && current=='=')
                            	{	
	                            	cout<<"\t"<<"O2"<<"\t+="<<endl;
	                            	continue;
                            	}
                            	if(next=='-' && current=='-')
                            	{	
	                            	cout<<"\t"<<"O3"<<"\t--"<<endl;
	                            	continue;
                            	}
                            	if(next=='-' && current=='=')
                            	{	
	                            	cout<<"\t"<<"O4"<<"\t-="<<endl;
	                            	continue;
                            	}
                            	break;
                            	}
                }
                if(l==N){
                    if(buffer[1]=='"')
                        check_literal(buffer+1);
                    else
                        check_symbol(buffer);              
                    }
            }
                i=0;
                if(l!=N){
                if(terminal[k].ter.c_str()[0]==' ')
                	cout<<"\t"<<terminal[k].token<<"\t"<<"\' \'"<<endl;	
                else if	(terminal[k].ter.c_str()[0]=='\n')
                	cout<<"\t"<<terminal[k].token<<"\t"<<"\\"<<"n"<<endl;
                else
	                cout<<"\t"<<terminal[k].token<<"\t"<<next<<endl;
				}               
                //if(l==N){
                //current=next;
                //fin.get(next);     
                //}
            }
            
        }
        current=next;
        

    }
    cout<<"\nSYMBOL TABLE : \n";
    for(int k=0;k<symcounter;k++){
    	cout<<"\t"<<symbol[k].token<<"\t"<<symbol[k].sym<<endl;
    }
     cout<<"\nLITERAL TABLE : \n";
    for(int k=0;k<litcounter;k++){
    	cout<<"\t"<<literal[k].token<<"\t"<<literal[k].lit<<endl;
    }

}
