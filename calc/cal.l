%{
    #include<stdio.h>
    #include"y.tab.h"
%}

%%
[0-9]+ {
    yylval = atoi(yytext);
    return NUMBER;
}

[+,-,/,*,%] return yytext[0] ;

\t ;

\n return 0;

. {
    yyerror();
}
%%

    int yywrap(){
        return 1;
    }