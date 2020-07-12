%{
#include "y.tab.h" 
%}
alpha [A-Za-z]
digit [0-9]
%%
while    return WHILE;
{digit}+    return NUM;
{alpha}({alpha}|{digit})*    return ID;
"<="    return LE;
">="    return GE;
"=="    return EQ;
"!="    return NE;
"||"    return OR;
"&&"    return AND;
[ \t\n]  ;
.    return yytext[0];
%%
int yywrap(void){return 1;}
