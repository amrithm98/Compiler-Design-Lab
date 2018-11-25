%{
    #include<stdio.h>
    #include<stdlib.>
    int yylineno;
%}

%option noyywrap

letter [A-Za-z]
digit [0-9]

%%
"prog"          {   return PROG; }
"begin"         {   return BEG; }
"then"          {   return THEN; }
"if"            {   return IF; }
"else"          {   return ELSE; }
"endif"         {   return EIF; }
"endwhile"      {   return EWHILE; }
"end"           {   return END; }
"while"         {   return WHILE; }
"do"            {   return DO; }
"integer"       {   return INT; }
","             {   return COMMA; }
";"             {   return SEMICOLON; }
"."             {   return DOT; }
":="            {   return ASSIGN; }
"="             {   return EQUAL; }
"<"             {   return LT; }
">"             {   return GT; }
[-+/*)()]       {   return yytext[0]; }
"write"         {   return WRITE;   }
{letter}({letter}|{digit})* {   yylval.name = strdup(yytext); return ID;  }
[0-9]+          {   yylval.num = atoi(yytext); return NUM; }
[ \t]           {   ;   }
[\n]            {   yylineno++; }
%%
