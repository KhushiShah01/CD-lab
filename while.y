%{
#include<stdio.h>
%}
%token TYPE WHILE COMMA SC ID RELOP OP LIT NL OPL OPB
%token LPAREN RPAREN
%token LBRACE RBRACE
%%
start: WHILE LPAREN ID RELOP ID RPAREN code NL{printf("Valid"); return 0;}
code: line SC| LBRACE block RBRACE
line: line ID | ID;
block: block line SC NL| line SC NL;
%%
int yyerror(const char* s){printf("\nError");
return 1;}
main(){
yyparse() ;
}