%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "y.tab.h"
%}

%option noyywrap

%%
[0-9]+                  {   yylval.val = atoi(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9]*   {   yylval.name = strdup(yytext); return ID; }
[-+*/]                  {   return yytext[0]; }
[ \t\n]                 {   ;   }
%%

