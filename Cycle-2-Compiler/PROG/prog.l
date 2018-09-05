%{
#include "prog.h"
%}

%%
":="			return ASSIGN_OP;
;			return SEMICOLON;
"+" 			return ADD_OP;
-                       return SUB_OP;
"*"                     return MUL_OP;
"/"			return DIV_OP;
=                       return EQU_OP;
"<"			return LT;
">"                     return GT;
"<="                    return LTE;
">="                    return GTE;
[(,),{,}]		return LITERAL;
read|write|prog|begin|integer|while|do|if|else|endif|end|then|endwhile                 return KEYWORD;
[a-zA-Z][_a-zA-Z0-9]* 	return IDENTIFIER;
[1-9][0-9]*		return DIGIT;
[ \t \n]		;
%%

int yywrap(void)
{
	return 1;
}
