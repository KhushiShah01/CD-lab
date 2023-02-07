%{
    #include<stdio.h>
    #include<stdlib.h>
    int flag;
%}


%token NUMBER

%left '+' '-'
%left '/' '*' '%'
%left '(' ')'

%%
ArithmeticExpression: E { 
    if(flag == 0)
        printf("Result = %d", $$);
    exit(0);
};

E:E'+'E     {$$ = $1+$3;}  
   |E'-'E    {$$ = $1+$3;}
   |E'/'E    {$$ = $1+$3;}
   |E'*'E    {$$ = $1+$3;}
   |E'%'E    {$$ = $1+$3;}
   |'('E')' {$$ = $2;}
   |NUMBER {$$ = $1;}
;
%%

void main(){
    printf("Enter arithmetic expression: ");
    yyparse();
    if(flag == 0) {
        printf("Valid Arithmetic Expression");
    }

}

void yyerror(){
    flag = 1;
    printf("\nEntered arithmetic expression is Invalid\n\n");

}