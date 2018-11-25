#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define STACK_SIZE 100
#define CODE_SIZE 100

#define RES     1
#define READ    2
#define WRITE   3
#define GOTO    4
#define LT      5
#define GT      6
#define EQ      7

#define JMP_FALSE   8
#define LOAD_INT    9
#define LOAD_VAR    10

#define STORE   11
#define ADD     12
#define MUL     13
#define DIV     14
#define SUB     15
#define HALT    16

struct instruction{

    char opcode[10];
    int operand;
};

struct instruction code_seg[CODE_SIZE];
int* data_seg = 0;
int stack[STACK_SIZE];
int top = -1;

int pop();
void push(int);
int convert_opcode(char[]);

int main(int argc , char** argv)
{
    char opcode[10];
    int operand;
    int temp;
    int line = 1;
    int code_size = 0;
    int left , right;
    FILE *input;

    if(strcmp(argv[1] , "stdin") == 0)
        input = stdin;
    else
        input = fopen(argv[1] , "r");


    while(1){

        if(line > code_size){

            code_size++;
            fscanf(input,"%s %d" , code_seg[code_size].opcode , &code_seg[code_size].operand);
            continue;    
        } 

        strcpy(opcode , code_seg[line].opcode);
        operand = code_seg[line].operand;

        printf("%d %s  %d\n" , line ,opcode , operand);

        switch(convert_opcode(opcode)){

            case RES    :   data_seg = (int*) malloc(operand * sizeof(int));
                            break;

            case READ   :   scanf("%d", &temp);
                            data_seg[operand] = temp;
                            break;

            case WRITE  :   printf("%d\n" , pop());
                            break;

            case GOTO   :   line = operand - 1; // line++ after switch()
                            break;

            case LT     :   right = pop();
                            left = pop();

                            if(left < right)
                                push(1);
                            else
                                push(0);

                            break;

            case GT     :   right = pop();
                            left = pop();

                            if(left > right)
                                push(1);
                            else
                                push(0);

                            break;

            case EQ     :   right = pop();
                            left = pop();

                            if(left == right)
                                push(1);
                            else
                                push(0);

                            break;
            
            case JMP_FALSE  :   if( pop() == 0 )
                                    line = operand-1; //line++ after switch()                                
                                break;

            case LOAD_VAR   :   push(data_seg[operand]);
                                break;

            case LOAD_INT   :   push(operand);
                                break;

            case STORE  :   data_seg[operand] = pop();
                            break;

            case ADD    :   right = pop();
                            left = pop();
                            push( left + right );
                            break;

            case MUL    :   right = pop();
                            left = pop();
                            push( left * right );
                            break;

            case DIV    :   right = pop();
                            left = pop();
                            push( left / right );
                            break;

            case SUB    :   right = pop();
                            left = pop();
                            push( left - right );
                            break;
            
            case HALT   :   exit(0);

            default     :   printf("Error : Unknown command...\n");
        }

        line++;
    }

    return 0;
}


int pop(){

    if(top == -1){

        printf("Error : stack underflow...\n");
        exit(0);
    }

    top--;

    return stack[top+1];
}

void push(int n){

    if(n == STACK_SIZE-1){

        printf("Error : stack overflow...\n");
        exit(0);
    }

    top++;

    stack[top] = n;

}

int convert_opcode(char opcode[]){

    if(strcmp(opcode , "res") == 0)
        return RES;
    
    if(strcmp(opcode , "read") == 0)
        return READ;

    if(strcmp(opcode , "write") == 0)
        return WRITE;

    if(strcmp(opcode , "goto") == 0)
        return GOTO;

    if(strcmp(opcode , "lt") == 0)
        return LT;

    if(strcmp(opcode , "eq") == 0)
        return EQ;
    
    if(strcmp(opcode , "gt") == 0)
        return GT;

    if(strcmp(opcode , "jmp_false") == 0)
        return JMP_FALSE;

    if(strcmp(opcode , "load_var") == 0)
        return LOAD_VAR;

    if(strcmp(opcode , "load_int") == 0)
        return LOAD_INT;

    if(strcmp(opcode , "store") == 0)
        return STORE;
    
    if(strcmp(opcode , "add") == 0)
        return ADD;

    if(strcmp(opcode , "mul") == 0)
        return MUL;

    if(strcmp(opcode , "div") == 0)
        return DIV;

    if(strcmp(opcode , "sub") == 0)
        return SUB;
        
    if(strcmp(opcode , "halt") == 0)
        return HALT;

    return -1;
}