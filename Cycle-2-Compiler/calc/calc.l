%{
#include "calc.h"
%}

%%
;			return SEMIC;
"+" 			return ADD_OP;
-                       return SUB_OP;
"*"                       return MUL_OP;
=                       return EQU_OP;
"print"                 return KEYWORD;
[a-zA-Z][_a-zA-Z0-9]* 	return IDENTIFIER;
[1-9][0-9]*		return DIGIT;
[ \t \n]		;
%%

int yywrap(void)
{
	return 1;
}
