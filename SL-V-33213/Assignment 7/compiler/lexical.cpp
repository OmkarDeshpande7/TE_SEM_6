#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;
fstream fin,fout;
struct keywords{
    string key,token; 
};

struct terminals{
    string ter,token;
}terminal[20];

struct symbols{
    string sym,token;
}symbol[20];

struct literals{
    string lit,token;
}literal[20];

int main(){
    char current,next,buffer[50];
    int i=0;
    keywords keyword[20]={{"int","K1"},{"char","K2"},{"float","K3"},{"auto","K4"},
                            {"do","K5"},{"while","K6"},{"for","K7"},{"struct","K8"},
                            {"if","K9"},{"continue","K10"},{"break","K11"}};
    terminals terminal[20]={{" ","T1"},{",","T2"},{"{","T3"},{"}","T4"},
                            {"(","T5"},{")","T6"},{";","T7"},{"[","T8"},
                            {"]","T9"},{"+","T10"},{"-","T11"},{"/","T12"},{"*","T13"},{"\n","T14"}};
    fin.open("input.c",ios::in);
    fout.open("output.c",ios::out);
    fin.get(current);
    fin.seekg(1);
    while(fin.get(next)){

        buffer[i++]=current;
        buffer[i]='\0';
        for(int k=0;k<14;k++){
            if(next==terminal[k].ter.c_str()[0]){
                
                for(int j=0;j<11;j++){
                    if(!strcmp(keyword[j].key.c_str(),buffer)){
                        cout<<keyword[j].token<<" "<<endl;
                        break;
                        }
                    
                }
                i=0;
                cout<<terminal[k].token<<" "<<next<<endl;
                fin.get(next);
                current=next;
                
                continue;
                
            }
            
        }
        current=next;
        

    }

}
