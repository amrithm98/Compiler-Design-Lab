%{
	#include<stdio.h>
	#include<stdlib.h>
	void yyerror();
	int sym[52];
	int value(char c);
	void update(char s,int val);
%}

%union{int n; char id;}
%start stmt
%token print end
%token <n> num
%token <id> identifier
%type <n> stmt exp term
%type <idnt> assign
%right '='
%left '+' '-'
%left '*' '/'
%%

stmt : assign ';' 						{;}
	| end ';' 							{exit(EXIT_SUCCESS);}
	| print exp ';' 					{printf("\nValue is : %d\n",$2);}
	| stmt assign ';' 					{;}
	| stmt print exp ';' 				{printf("\nValue is : %d\n",$3);}
	| stmt end ';' 						{exit(EXIT_SUCCESS);};

assign : identifier '=' exp 			{update($1,$3);}
;

exp	: term			{$$ = $1;}
	| '(' exp ')'	{$$ = $2;}
	| exp '=' exp 	{$$ = $3;}
	| exp '+' exp	{$$ = $1+$3;}
	| exp '-' exp	{$$ = $1-$3;}
	| exp '*' exp	{$$ = $1*$3;}
	| exp '/' exp	{$$ = $1/$3;}
;

term : identifier 	{$$ = value($1);}
	| num			{$$ = $1;}
; 

%%

int idx(char s)
{
	int i = -1;
	if(islower(s))
	{
	    i = s - 'a' + 26;
	}
	else if(isupper(s))
	{
	    i = s-'A';
	}
	return i;
}

int value(char s)
{
	int i = idx(s);
	return sym[i];
}

void update(char s,int val)
{
	int i = idx(s);
	sym[i] = val;
}

int main(void)
{
	int j;

	for(j = 0; j < 52; j++)
		sym[j] = 0;

	return yyparse();	
}

void yyerror()
{
	
}
