%{
#include<stdio.h>
#include "y.tab.h"
%}
%%
int|float|char return TYPE;
while return WHILE;
"," return COMMA;
";" return SC;
[a-zA-Z0-9]* return ID;
[<,<=,>,>=,!=,==] return RELOP;
"=" return OP;
"\t" ;
" " ;
\( return LPAREN;
\) return RPAREN;
"{" return LBRACE;
"}" return RBRACE;
"\'" return LIT;
"\n" return NL;
. {
yyerror();
}
%%
int yywrap()
{return 1;}