%{
	#include "y.tab.h"
%}
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
int yywrap(void)
{
	return 1;
}
