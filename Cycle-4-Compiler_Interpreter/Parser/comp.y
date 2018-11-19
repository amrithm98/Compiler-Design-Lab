%{
#include<stdio.h>
int yylex();
void yyerror(const char *s);
%}

// %token PROG  NUMBER BEGI END DO /*<num>*/ INTEGER /*<charvalue>*/ IDENTIFIER IF ELSE WHILE THEN ENDIF ENDWHILE READ WRITE PLUS MINUS MULT DIV DOT COMMA EQUAL LS

%token PROG
%token INT
%token BEG
%token READ
%token IF
%token THEN
%token ELSE
%token EIF
%token WHILE
%token DO
%token EWHILE
%token WRITE
%token END
%token<charvalue> IDENTI
%token<num> NUM
%token LS
%token DOT
%token COMMA
%token EQUAL
%token PLUS
%token MINUS
%token MULT
%token DIV

%union 
{
  char charvalue;
  int num; 
}

%start Pro
%%


Pro: PROG declarations BEG command_sequence END

declarations: INT id_seq IDENTI DOT
|
;

id_seq:id_seq IDENTI COMMA
|
;

command_sequence:command_sequence command COMMA
|
;

command : IDENTI  EQUAL expression
| IF expression THEN command_sequence ELSE command_sequence EIF
| WHILE expression DO command_sequence EWHILE
| READ IDENTI
| WRITE expression
|
;

expression : NUM | IDENTI | '(' expression ')'
| expression PLUS expression | expression MULT expression
| expression MINUS expression | expression DIV expression
| expression LS expression
;

%%

// struct sym{
// 	char name;
// 	int val;
// };

void yyerror(const char *str)
{
//   fprintf(stderr,"error: %s\n",str);
}

int yywrap()
{
  return 1;
}

int main()
{
  yyparse();
  printf("\nThe prog was successfully parsed and acepted");
  return 0; 
}
