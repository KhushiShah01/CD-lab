%{
#include "y.tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int LineNo=1;
%}
identifier [a-zA-Z][_a-zA-Z]*
number [0-9]+
%%
{identifier} {return VARIABLE;}
{number} {return NUM;}
"=" {return ASSIGNOP;} 
"+" {return ADD;};
"*" {return MUL;};
"-" {return SUB;};
"/" {return DIV;};
\t ;
\n LineNo++;
. yytext[0];
%%
int yywrap(void){
return 1;
}
