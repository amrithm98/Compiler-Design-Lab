%{
    #include<stdio.h>
    #include<iostream>
    using namespace std;

    int yylex();
    void yyerror(const char *s);

    void printError(int code);
	void write_machine_code();
	extern int line_no;
    extern char lastID[100];

	int data_offset = 0;

    struct sym_rec 
    {
        char *name;  //name of the symbol
        int data;     //Data
        struct sym_rec *next; //link field
        int data_offset;//will be used during code generation phase.
    };

    extern struct sym_rec;
    struct sym_rec *sym_record;

    struct sym_rec * put_symbol(char *name, int data);
    struct sym_rec * get_symbol(char *name);
    void install(char *name);
    void displaySymTab();

    char machine_code[1000];
	int  pos = 0;

	struct stack_node{
		int pos;
		struct stack_node* next;
	};
	stack_node *stack_top = 0;
	void push(int pos);
	int  pop();
%}

%union 
{
  char *name;
  int num; 
  int offset;
}

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
%token LS
%token DOT
%token COMMA
%token EQUAL
%token PLUS
%token MINUS
%token MULT
%token DIV
%token SEMICOLON
%token GT

%token NUM IDENTI
%type<num> expression NUM
%type<name> IDENTI

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%left '<' '>'

%start Pro
%%


Pro:    PROG declarations                                   { 
                                                                pos += sprintf( machine_code + pos , "res\t\t%d\n" , data_offset/4);
                                                            }

        BEG command_sequence END                            {
                                                                pos += sprintf( machine_code + pos , "halt\t\t0\n");
                                                            }

declarations: INT id_seq IDENTI DOT                         { 
                                                                printf("\nIdentifier : %s", $3);
                                                                install($3); 
                                                            }
        |
        ;

id_seq:id_seq IDENTI COMMA                                  { 
                                                                printf("\nIdentifier : %s", $2);
                                                                install($2); 
                                                            }
        |
        ;

command_sequence:command_sequence command SEMICOLON
        |
        ;

command : IDENTI EQUAL expression                           {
                                                                ////context_check($1);
                                                                pos += sprintf(machine_code + pos , "store\t\t%d\n" , $3);
                                                                // printf("\nIdentifier = Expr : %s %d", $1, $3); 
                                                                put_symbol($1, $3); 
                                                            }  

        | IF expression THEN                                {
                                                                pos += sprintf(machine_code + pos , "jmp_false\tL1\n");
                                                            }

          command_sequence                                  {
										                        pos += sprintf(machine_code + pos , "goto\t\tL2\n");
                                                            }
          ELSE command_sequence EIF                         

        | WHILE expression DO                               {
                    										    pos += sprintf(machine_code+pos , "jmp_false\tL2\n");
                                                            }

          command_sequence                                  {
                                                                pos += sprintf(machine_code+pos , "goto\t\tL1\n");
                                                            }
          EWHILE                

        | READ IDENTI                                       {   
                                                                install($2);
                                                                int offset = get_symbol($2)->data_offset/4; 
                                                                //context_check(lastID);
										                        pos += sprintf(machine_code + pos , "read\t\t%d\n" ,offset);
                                                            }

        | WRITE expression                                  {
                                                                pos += sprintf(machine_code+pos , "write\t\t0\n");
                                                            }
        |
        ;

expression : NUM                                            { 						
                                                                pos += sprintf(machine_code+pos , "load_int\t%d\n" , $1);
                                                                $$ = $1; 
                                                            }

| IDENTI                                                    {
                                                                int offset = get_symbol($1)->data_offset/4;
    						                                    pos += sprintf(machine_code+pos , "load_var\t%d\n" , offset);
                                                                $$ = (get_symbol($1)!= NULL)? get_symbol($1)->data:0;
                                                            }

| '(' expression ')'                                        {   $$ = $2;    }

| expression PLUS expression                                {
    									                        pos += sprintf(machine_code+pos , "add\t\t0\n");
                                                                $$ = $1+$3;
                                                            }

| expression MULT expression                                {
    									                        pos += sprintf(machine_code+pos , "mul\t\t0\n");
                                                                $$ = $1*$3;
                                                            }

| expression MINUS expression                               {
    									                        pos += sprintf(machine_code+pos , "sub\t\t0\n");
                                                                $$ = $1-$3;
                                                            }

| expression DIV expression                                 {
    									                        pos += sprintf(machine_code+pos , "div\t\t0\n");
                                                                $$ = $1/$3;
                                                            }

| expression LS expression                                  {
    									                        pos += sprintf(machine_code+pos , "lt\t\t0\n");
                                                                $$ = $1<$3;
                                                            }

| expression GT expression                                  {
    									                        pos += sprintf(machine_code+pos , "gt\t\t0\n");
                                                                $$ = $1>$3;
                                                            }
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

struct sym_rec * get_symbol(char *name)
{
    struct sym_rec *temp = sym_record;
    while(temp != NULL)
    {
        if(strcmp(temp->name, name) == 0)
          return temp;

        temp = temp->next;
    }

    return NULL;
}

void install(char *name)
{
    
    struct sym_rec *temp = get_symbol(name);

    if(temp == NULL)
    {
        temp = (struct sym_rec*)malloc(sizeof(struct sym_rec));
        temp->name = name;
        temp->data = 0;
        temp->next = sym_record;
        temp->data_offset = data_offset;
        data_offset = data_offset + 4;
        sym_record = temp;
    }
}

struct sym_rec *put_symbol(char *name, int data)
{
    struct sym_rec *temp = get_symbol(name);

    if(temp == NULL)
    {
        cout << "\nERROR: Undefined Variable " << name << endl;
        return NULL;
    }

    temp->data = data;

    return temp;
}

void displaySymTab()
{
    cout << "\nSymbol Table : ";

    struct sym_rec *temp = sym_record;
    while(temp != NULL)
    {
        if(strcmp(temp->name,"end") != 0)
          cout << "\nName : " << temp->name << " Value : " << temp->data << " Offset: " << temp->data_offset << "\n";
        temp = temp->next;
    }
}

void write_machine_code()
{
	printf("\nStack Machine Code : \n\n%s\n" , machine_code);
}

int main()
{
    sym_record = (struct sym_rec *)malloc(sizeof(struct sym_rec));
    sym_record->name = "end";
    sym_record->data = -1;
    sym_record->next = NULL;
    
    yyparse();
    printf("\nThe program was successfully parsed and accepted\n");
    displaySymTab();
    write_machine_code();

    return 0; 
}
