#include<bits/stdc++.h>
using namespace std;


/*

Declare -> Type var;
Type -> int | float | char
var -> var,id | id



Remove left recursion;
var -> id,var_dash
var_dash -> id,var_dash | ^

*/
bool isDigit(char c){
	if(c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' )
		return true;
	return false;
}
bool var_dash();
char buffer[50];

bool Type(){
	char temp[50];
	strcpy(temp,buffer);
	char *token = strtok(temp, " "); 
	if(!strcmp(token,"int") || !strcmp(token,"float") || !strcmp(token,"char"))
		return true;
	return false;
}

bool Var(){

	char temp[50];
	strcpy(temp,buffer);
	char *token = strtok(temp, " ");
	if(token && isDigit(token[0]))
		{
			cout<<"Invalid identifier "<<token<<" !\n";
			return false; 
		}
	
	if(var_dash()) 
		return true;
	return false;
}

bool var_dash(){

	char temp[50];
	strcpy(temp,buffer);
	char *token = strtok(temp, " ");
    
    while (token != NULL) 
    { 
		
        token = strtok(NULL, ",");

		if(token && isDigit(token[0]))
		{
			cout<<"Invalid identifier "<<token<<" !\n";
			return false; 
		}
		if(token && token[strlen(token)-1]==';')
			return true;
    }
	return true;

}


bool Declare(){
	
	if(Type() && Var() && buffer[strlen(buffer)-1]==';')
		return true;
	return false;
}

int main(){
cout<<"Enter the string : ";
cin.getline(buffer,50);

if(Declare())
	cout<<"String Accepted !";
else
	cout<<"String Rejected !";
}
