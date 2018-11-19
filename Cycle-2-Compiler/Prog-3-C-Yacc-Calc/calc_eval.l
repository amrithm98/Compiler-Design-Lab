%{
	#include <stdio.h>
	#include "y.tab.h"
%}

%option noyywrap

%%
"print"	    {return print;}
"exit"	    {return end;}
[a-zA-Z]    {yylval.id = yytext[0]; return identifier;}
[0-9]+      {yylval.n = atoi(yytext); return num;}
[\t\n]      ;
[-=+/;()]     {return yytext[0];}
"*"	        {return yytext[0];}
.	        {ECHO; yyerror();}
%%
