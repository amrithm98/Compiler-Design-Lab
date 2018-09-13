%{
	#include<stdlib.h>
	#include<stdio.h>
	void yyerror();
	int n = 1;
%}

%start stmt
%token ID

%%
stmt : ID
;
%%
void main()
{
	while(n)
	{
	printf("INPUT AN IDENTIFIER : ");
	yyparse();
	printf("VALID IDENTIFIER\n\n");
	}
}
void yyerror()
{
	printf("INVALID IDENTIFIER\n\n");
	exit(0);
}
