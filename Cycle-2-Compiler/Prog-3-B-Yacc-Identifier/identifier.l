%{
	#include "y.tab.h"
%}

%%
[a-zA-Z_][_a-zA-Z0-9]*  {return ID;}
[\t]	            {;}
[\n]	            {return 0;}
.	                {return yytext[0];}
%%

int yywrap(void)
{
	return 1;
}
