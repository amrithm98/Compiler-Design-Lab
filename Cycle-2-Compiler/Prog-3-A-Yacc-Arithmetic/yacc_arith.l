%{
	#include "y.tab.h"
%}
%%
[a-zA-Z_][a-zA-Z0-9]* 	{return ID;}
[0-9]+					{return NUM;}
[\t]					{;}
[\n]					{return 0;}
.						{return yytext[0];}
%%
int yywrap(void)
{
	{return 1;}
}