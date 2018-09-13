%{
#include "prog.h"
%}

letter [a-zA-Z]
digitt [0-9]
id {letter}*|({letter}{digitt})+
notid ({digitt}{letter})+

%%

"."				return DOT;
":="			return ASSIGN_OP;
;				return SEMICOLON;
"+" 			return ADD_OP;
-               return SUB_OP;
"*"             return MUL_OP;
"/"				return DIV_OP;
=               return EQU_OP;
"<"				return LT;
">"             return GT;
"<="            return LTE;
">="            return GTE;
[(,),{,}]		return LITERAL;
read|write|prog|begin|integer|while|do|if|else|endif|end|then|endwhile                 return KEYWORD;
{id}			return IDENTIFIER;
{notid} 		{ printf("\n%s is not an identifier at line %d\n", yytext,yylineno); exit(0);}
[1-9][0-9]*		return DIGIT;
\n				{yylineno++;}
[ \t]			;
%%

int yywrap(void)
{
	return 1;
}
