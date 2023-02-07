%{
#include<string.h>
#include<stdio.h>
#include <stdlib.h>
int yylex();
extern char* yytext;
int yyerror();
extern FILE *yyin;
struct quad{
char op[5];
char arg1[10];
char arg2[10];
char result[10];
}QUAD[30]; 
int Index=0,tIndex=0;
extern int LineNo; 
void AddQuadruple(char op[5],char arg1[10],char arg2[10],char 
result[10]) {
// Add code here to add a new quadruple to the QUAD array
strcpy(QUAD[Index].op,op);
strcpy(QUAD[Index].arg1,arg1);
strcpy(QUAD[Index].arg2,arg2);
sprintf(QUAD[Index].result,"t%d",tIndex++);
strcpy(result,QUAD[Index++].result);
} 
%}

%union
{
char var[10];
}

%token <var> NUM VARIABLE RELOP ARTHOP ASSIGNOP ADD MUL SUB DIV
%type <var> START EXPR TERM PRIMARY
%left '-' '+'
%left '*' '/' 


%%
START: PRIMARY ASSIGNOP EXPR {strcpy(QUAD[Index].op,"=");
strcpy(QUAD[Index].arg1,$3);
strcpy(QUAD[Index].arg2," ");
strcpy(QUAD[Index].result,$1);
strcpy($$,QUAD[Index++].result);
}
;
EXPR: EXPR ADD TERM {AddQuadruple("+",$1,$3,$$);}
| EXPR SUB TERM {AddQuadruple("-",$1,$3,$$);}
| TERM
;
TERM: TERM MUL PRIMARY {AddQuadruple("*",$1,$3,$$);}
| TERM DIV PRIMARY {AddQuadruple("*",$1,$3,$$);}
| PRIMARY
;
PRIMARY: VARIABLE {strcpy($$, yytext);}
| NUM {strcpy($$, yytext);}
;


%%


int main(){
    FILE *fp;
    int i;
    fp=fopen("arth.txt","r");
    if(!fp){
        printf("\n File not found");
        exit(0);
    }
    yyin=fp;
    yyparse();
    printf("\n\n\t\t ----------------------------""\n\t\t Pos Operator 
    \tArg1 \tArg2 \tResult" "\n\t\t--------------------");
    for(i=0;i<Index;i++){
        printf("\n\t\t %d\t %s\t %s\t 
        %s\t%s",i,QUAD[i].op,QUAD[i].arg1,QUAD[i].arg2,QUAD[i].result);
    }
    printf("\n\t\t -----------------------");
    printf("\n\n"); 
    return 0; 
}

int yyerror(){
    printf("\n Error on line no:%d %s",LineNo, yytext);
}
