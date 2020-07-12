#include<iostream>
#include<string.h>
#include<string>
#include <bits/stdc++.h>
#include<fstream>
using namespace std;

char registers[4][6]={"AREG","BREG","CREG","DREG"}; 

struct statement
{
	char label[10];
	char mnemonic[10];
	char op1[10];
	char op2[10];
};
struct mnemonics
{
	char name[10];
	char type[3];
	int opcode;
	int size;
} mnemonic[20];

struct literals
{
    char name[10]; 
    int address; 
} literal[20];

struct symbols
{
    char name[10]; 
    int address; 
    int value;
    int type;
} symbol[20];

int number_of_mnemonics=0,number_of_symbols=0,number_of_literals=0;
int lc=0;
fstream fout;


void check_symbol(string wc)
{
	int flag_sym=0;
    fstream symtab;
    symtab.open("symtab.txt",ios::app|ios::out);

	for(int k=0;k<number_of_symbols;k++)
	{
		if(!strcmp(symbol[k].name,wc.c_str()))
		{
			
			flag_sym=1;
            fout<<"(S, "<<k<<") "<< lc<<endl;
			break;
		}
	}
	if(flag_sym==0)
	{
		strcpy(symbol[number_of_symbols].name,wc.c_str());
		symbol[number_of_symbols].address=-1;
        fout<<"(S, "<<number_of_symbols<<") "<< lc<<endl;
        symtab<<wc<<" "<<lc<<endl;
		number_of_symbols++;
	}
	flag_sym=0;
	symtab.close();
}

void check_literal(string wc)
{
	
	int flag_lit=0;
    fstream littab;
    littab.open("littab.txt",ios::app | ios::out);

	for(int k=0;k<number_of_literals;k++)
	{
		if(!strcmp(literal[k].name,wc.c_str()))
		{
			flag_lit=1;
            fout<<"(L, "<<k<<") "<< lc<<endl;
			break;
		}
	}
	if(flag_lit==0)
	{
		
		strcpy(literal[number_of_literals].name,wc.c_str());
		literal[number_of_literals].address=-1;
        fout<<"(L, "<<number_of_literals<<") "<< lc<<endl;
        littab<<wc<<" "<<lc<<endl;
		number_of_literals++;
	}
	flag_lit=0;	
	littab.close();
}




int main(){
    fstream fin,mot;
    statement templine;
    int i = 0,lit_count=0;
    string line;    
    mot.open("MOT.txt",ios::in);
    fin.open("test4.asm",ios::in);
    fout.open("out.txt",ios::out);
    while(!mot.eof()){
        mot>>mnemonic[i].name>>mnemonic[i].type>>mnemonic[i].opcode>>mnemonic[i++].size;
    }
    number_of_mnemonics=i;
	// i--;
    // mot.seekg(ios::beg);
    // while(i--){
    //     // Write line in file 
    //     cout<<mnemonic[i].name<<" "<<mnemonic[i].type<<" "<<mnemonic[i].opcode<<" "<<mnemonic[i].size<<endl;
        
    // }
    mot.close();
    string temp;
        fin>>temp;
        if(!strcmp(temp.c_str(),"START"))
        {
            fin>>lc;
			
            fout<<"(AD, 00) "<<lc<<endl;
            while(!fin.eof()){
				fin>>temp;
				
				if(!strcmp(temp.c_str(),"STOP"))
					break;
				else{
					
					for(i=0;i<number_of_mnemonics;i++){

						if(!strcmp(temp.c_str(),mnemonic[i].name)){
							if(!strcmp(mnemonic[i].type,"IS")){
								
								if(!strcmp(mnemonic[i].name,"READ") || !strcmp(mnemonic[i].name,"PRINT")){
									fin>>temp;
									check_symbol(temp.c_str());
									break;	
								}
								else{
									fout<<"("<<mnemonic[i].type<<", "<<mnemonic[i].opcode<<") ";
									fin>>temp;
									for(int j=0;j<4;j++){
										if(!strcmp(temp.c_str(),registers[j]))
										{
											fout<<"(R, "<<j+1<<")";
											fin>>temp;
							
											if(temp.c_str()[0]=='\'')
												check_literal(temp.c_str());
											
											else
												check_symbol(temp.c_str());
												break;
										
										}
									
							
									}
								}	
								lc+=mnemonic[i].size;
								break;
							}
						
							else if(!strcmp(mnemonic[i].type,"AD")){
							
								if(!strcmp(mnemonic[i].name,"LTORG")){
									fout<<"(AD 00) "<<lc<<endl;
									for(int k=lit_count;k<number_of_literals;k++){
										literal[k].address=lc;
										lc++;
									}
									lit_count=number_of_literals;
									
									break;
									}
									else if(!strcmp(mnemonic[i].name,"ORIGIN"))
									{
										fin>>temp;
										cout<<temp;
										int l;
										size_t  found;
										fout<<"(AD 00) ";
										for(l=0;l<=number_of_symbols;l++){
											found = temp.find(symbol[l].name); 
											if (found != string::npos){
												fout<<"(S, "<<l<<")"<<temp.substr(strlen(symbol[l].name))<<endl;
												lc=lc + atoi(temp.substr(strlen(symbol[l].name)).c_str());
												break;
												}
											}
										
										break;
									}
							}
						
						}
					
					}
					
				}
				if(i==number_of_mnemonics)
						check_symbol(temp);
            }


			while(!fin.eof()){
				int flag_lit=0,flag_sym=0;
				fin>>temp;
				if(!strcmp(temp.c_str(),"END"))
					break;
				for(int k=0;k<number_of_symbols;k++){
					if(!strcmp(symbol[k].name,temp.c_str())){		
					flag_sym=1;
					fout<<"(S, "<<k<<") "<<lc<<endl;
					symbol[k].address=lc;
					break;
					}
				}
				if(flag_sym==0){
					strcpy(symbol[number_of_symbols].name,temp.c_str());
					symbol[number_of_symbols].address=lc;
					fout<<"(S, "<<number_of_symbols<<") "<<lc<<endl;
					number_of_symbols++;
				}
				flag_sym=0;
				fin>>temp; 
				if(!strcmp(temp.c_str(),"DC")){	
					fin>>temp;

					if(temp.c_str()[0]=='\'')
					{

						for(int p=lit_count;p<number_of_literals;p++)	{
							if(!strcmp(literal[p].name,temp.c_str()))	{
								flag_lit=1;
								fout<<"DC (L, "<<p<<") "<<lc;
								break;
							}
						}
						if(flag_lit==0){
							strcpy(literal[number_of_literals].name,temp.c_str());
							literal[number_of_literals].address=-1;
							fout<<"DC (L, "<<number_of_literals<<") "<<lc;
							number_of_literals++;
						}
						flag_lit=0;		
					}	
					lc++;
				}
				else if(!strcmp(temp.c_str(),"DS")){

					fin>>symbol[number_of_symbols].value;
					fout<<"DS, size="<<symbol[number_of_symbols].value<<endl;
					symbol[number_of_symbols].type=1;
					symbol[number_of_symbols].address=lc;
					lc+=symbol[number_of_symbols].value;
				}
			}




        }    
        else
       	{
       		cout<<"\nERROR CODE SHOULD BEGIN WITH START";
       		return 0;
       	}    
    

    
}
