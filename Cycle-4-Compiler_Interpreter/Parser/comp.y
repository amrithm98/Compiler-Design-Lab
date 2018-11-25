%{
    #include<stdio.h>
    #include<iostream>
    using namespace std;

    int yylex();
    void yyerror(const char *s);

    void printError(int code);
	void write_machine_code();
	extern int input_line_no;

	int data_offset = 0;

    struct sym_rec 
    {
        char *name;  //name of the symbol
        int data;     //Data
        struct sym_rec *next; //link field
        int data_offset;//will be used during code generation phase.
    };

    struct sym_rec *sym_record;

    struct sym_rec * put_symbol(char *name, int data);
    struct sym_rec * get_symbol(char *name);
    void install(char *name);
    void displaySymTab();
    void context_check(char *name);

    char machine_code[1000];
	int  pos = 0;
    int output_line_no = 1;

	struct stack_node{
		int pos;
		struct stack_node* next;
	};

	stack_node *stack_top = 0;
	void push(int pos);
	int  pop();
    void replace(char str[], int pos , int n);
    void write_machine_code_to_file(const char*);
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

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%left '<' '>'

%start Pro
%%


Pro:    PROG declarations                                   { 
                                                                pos += sprintf( machine_code + pos , "res\t\t%d\n" , data_offset/4);
                                                                output_line_no++;
                                                            }

        BEG command_sequence END                            {
                                                                pos += sprintf( machine_code + pos , "halt\t\t0\n");
                                                                output_line_no++;
                                                            }

declarations: INT id_seq IDENTI DOT                         { 
                                                                //printf("\nIdentifier : %s", $3);
                                                                install($3); 
                                                            }
        |
        ;

id_seq:id_seq IDENTI COMMA                                  { 
                                                                //printf("\nIdentifier : %s", $2);
                                                                install($2); 
                                                            }
        |
        ;

command_sequence:command_sequence command SEMICOLON
        |
        ;

command : IDENTI EQUAL expression                           {
                                                                context_check($1);
                                                                int offset = get_symbol($1)->data_offset/4;
                                                                pos += sprintf(machine_code + pos , "store\t\t%d\n" , offset);
                                                                // printf("\nIdentifier = Expr : %s %d", $1, $3); 
                                                                put_symbol($1, $3); 
                                                                output_line_no++;
                                                            }  

        | IF expression THEN                                {
                                                                //Push 000, replace it with next line of goto
                                                                push(pos + 11);
                                                                pos += sprintf(machine_code + pos , "jmp_false\t\t000\n");
                                                                output_line_no++;
                                                            }

          command_sequence                                  {
                                                                //Line after goto appear here
                                                                replace(machine_code, pop(), output_line_no + 1);
                                                                //Goto 000, replace it once you get 000
                                                                push(pos + 6);

										                        pos += sprintf(machine_code + pos , "goto\t\t000\n");
                                                                output_line_no++;
                                                            }

          ELSE command_sequence EIF                         {
                                                                replace(machine_code, pop(), output_line_no);
                                                            }

        | WHILE                                             {
                                                                push(output_line_no);
                                                            }

          expression DO                                     {
                                                                push(pos + 11);
                    										    pos += sprintf(machine_code+pos , "jmp_false\t\t000\n");
                                                                output_line_no++;
                                                            }

          command_sequence                                  {
                                                                int replace_pos = pop();
                                                                pos += sprintf(machine_code+pos , "goto\t\t%03d\n", pop());
                                                                output_line_no++;

                                                                replace(machine_code, replace_pos, output_line_no);
                                                            }
          EWHILE                

        | READ IDENTI                                       {   
                                                                context_check($2);
                                                                int offset = get_symbol($2)->data_offset/4; 
										                        pos += sprintf(machine_code + pos , "read\t\t%d\n" ,offset);
                                                                output_line_no++;
                                                            }

        | WRITE expression                                  {
                                                                pos += sprintf(machine_code+pos , "write\t\t0\n");
                                                                output_line_no++;
                                                            }
        |
        ;

expression : NUM                                            { 						
                                                                pos += sprintf(machine_code+pos , "load_int\t\t%d\n" , $1);
                                                                $$ = $1; 
                                                                output_line_no++;
                                                            }

| IDENTI                                                    {
                                                                int offset = get_symbol($1)->data_offset/4;
    						                                    pos += sprintf(machine_code+pos , "load_var\t\t%d\n" , offset);
                                                                $$ = (get_symbol($1)!= NULL)? get_symbol($1)->data:0;
                                                                output_line_no++;
                                                            }

| '(' expression ')'                                        {   $$ = $2;    }

| expression PLUS expression                                {
    									                        pos += sprintf(machine_code+pos , "add\t\t0\n");
                                                                $$ = $1+$3;
                                                                output_line_no++;
                                                            }

| expression MULT expression                                {
    									                        pos += sprintf(machine_code+pos , "mul\t\t0\n");
                                                                $$ = $1*$3;
                                                                output_line_no++;
                                                            }

| expression MINUS expression                               {
    									                        pos += sprintf(machine_code+pos , "sub\t\t0\n");
                                                                $$ = $1-$3;
                                                                output_line_no++;
                                                            }

| expression DIV expression                                 {
    									                        pos += sprintf(machine_code+pos , "div\t\t0\n");
                                                                $$ = $1/$3;
                                                                output_line_no++;
                                                            }

| expression LS expression                                  {
    									                        pos += sprintf(machine_code+pos , "lt\t\t0\n");
                                                                $$ = $1<$3;
                                                                output_line_no++;
                                                            }

| expression GT expression                                  {
    									                        pos += sprintf(machine_code+pos , "gt\t\t0\n");
                                                                $$ = $1>$3;
                                                                output_line_no++;
                                                            }
;

%%

// struct sym{
// 	char name;
// 	int val;
// };

void yyerror(const char*)
{
//   fprintf(stderr,"error: %s\n",str);
    
}

void printError(int err)
{
    
    switch(err)
    {
        case 1 : 
            printf("\nError: %d -> Compilation Error Found", input_line_no);
                break;
        case 2:
            printf("\nERROR: %d -> Redefinition Of Variable\n", input_line_no);
                break;
        case 3:
            printf("\nERROR: %d -> Undefined Variable\n", input_line_no);
            break;
    }
    exit(0);
}

int yywrap()
{
  return 1;
}

void context_check(char *name)
{
    if(get_symbol(name) == NULL)
        printError(3);
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
    else
        printError(2);
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
    int line_no = 0;
	printf("\nStack Machine Code : \n\n" );
	for(int i = 0 ; machine_code[i] != '\0' ; i++){
		if(i == 0 || machine_code[i-1] == '\n'){
			line_no++;
			printf("%03d : ", line_no);
		}
		printf("%c",machine_code[i]);
	}
}

void write_machine_code_to_file(const char* filename){
	FILE *output = fopen(filename , "w");
	fprintf(output , "%s", machine_code);
	fclose(output);
}

void push(int pos){
	struct stack_node *node = (struct stack_node*)malloc(sizeof(struct stack_node));
	node->pos = pos;
	node->next = stack_top;
	stack_top = node;
}

int pop(){
	if(stack_top == 0)
		return -1;
	int pos = stack_top->pos;
	struct stack_node* node = stack_top;
	stack_top = stack_top->next;
	free(node);
	return pos;
}

void replace(char str[] , int pos , int n){
	str[pos]   = n/100 + '0';
	str[pos+1] = (n%100) / 10 + '0';
	str[pos+2] = (n%10) + '0';
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
    write_machine_code_to_file("machine_code");
    return 0; 
}
