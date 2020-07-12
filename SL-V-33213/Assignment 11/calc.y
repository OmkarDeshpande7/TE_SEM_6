%{ 
#include<stdio.h> 
int flag=0; 
%} 

%token ID 

%left '+' '-'

%left '*' '/' '%'
%% 

Start: E{ 

		printf("\Answer is =%d\n", $$); 

		return 0; 
		}; 

E:E'+'E {$$=$1+$3;} 

|E'-'E {$$=$1-$3;} 

|E'*'E {$$=$1*$3;} 

|E'/'E {$$=$1/$3;} 

|E'%'E {$$=$1%$3;} 

|'('E')' {$$=$2;} 

| ID {$$=$1;} 

; 

%% 

void main() 
{ 
printf("\nEnter Any Arithmetic Expression : "); 

yyparse(); 
if(flag==0) 
printf("\nEntered arithmetic expression is Valid !\n\n"); 
} 

void yyerror() 
{ 
printf("\nEntered arithmetic expression is Invalid !\n\n"); 
flag=1; 
} 

