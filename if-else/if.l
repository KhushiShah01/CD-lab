%{
#include<stdio.h>
#include "y.tab.h"
extern int yylval;
%}
%%
int|float|char return TYPE;
if return IF;
else return ELSE;
"," return COMMA;
";" return SC;
[a-zA-Z0-9]* return ID;
[<,<=,>,>=,!=,==] return RELOP;
"=" return OP;
"\t" ;
" "  ; 
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
int yywrap(){return 1;}