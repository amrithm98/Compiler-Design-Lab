#include <iostream>
#include "calc.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(void)
{
	int ntoken;
	ntoken = yylex();
	while(ntoken)
	{
		printf("\nToken : %d Value : %s Line : %d",ntoken,yytext,yylineno);
		ntoken = yylex();
	}

	/*while(ntoken)
	{
		printf("\nToken :  %d",ntoken);
		if(ntoken == KEYWORD)
		{	
			ntoken = yylex();
			printf("\nPrinting %s",yytext);
			ntoken = yylex();
			continue;
		}
		printf("\nIdentifier %s is : ",yytext);

		ntoken = yylex();
		if(ntoken != EQU_OP)
		{
			printf("\nError : Undefined Syntax at line %d",yylineno);
			break;
		}
		ntoken = yylex();
		if(ntoken == DIGIT)
		{
			printf("%s",yytext);
		}
		else
		{	
			printf(" %s ",yytext);
			ntoken = yylex();
			printf(" %s ",yytext);
			ntoken = yylex();
			printf(" %s ",yytext);
		}
		ntoken = yylex();
	}*/
	return 0;
}

