#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#define RES 1
#define READ 2
#define WRITE 3
#define LOAD_VAR 4
#define LOAD_INT 5
#define LT 6
#define GT 7
#define EQ 8
#define JMP_FALSE 9
#define GOTO 10
#define STORE 11
#define ADD 12
#define MUL 13
#define SUB 14
#define DIV 15
#define HALT 16

struct Instruction
{
    string opCode;
    int operand;
};

int get_type(string type);

int main()
{
    ifstream infile("machinecode.txt");

    vector<Instruction> instructions;

    stack<int> operations;

    vector<int> dataSegment;

    while(1)
    {
        Instruction is;
        infile >> is.opCode >> is.operand;

        instructions.push_back(is);

        if(is.opCode == "halt")
            break;
    }

    int line = 0;
    int x, a, b;

    while(line < instructions.size())
    {
        int type = get_type(instructions[line].opCode);
        Instruction ins = instructions[line];

        cout << line << " " << ins.opCode << " " << ins.operand << endl;

        switch(type)
        {
            case RES:
                    dataSegment = vector<int> (ins.operand);
                    break;

            case READ:
                    cin >> x;
                    dataSegment[ins.operand] = x;
                    break;
            
            case WRITE:
                    x = operations.top();
                    operations.pop();
                    cout << "\nWrite : " << x << endl;
                    break;

            case LOAD_VAR:
                    operations.push(dataSegment[ins.operand]);
                    break;

            case LOAD_INT:
                    operations.push(ins.operand);
                    break;

            case LT:
                    b = operations.top();
                    operations.pop();
                    a = operations.top();
                    operations.pop();

                    if(a < b)
                        operations.push(1);
                    else
                        operations.push(0);
                    
                    break;
            case GT:
                    b = operations.top();
                    operations.pop();

                    a = operations.top();
                    operations.pop();

                    if(a > b)
                        operations.push(1);
                    else
                        operations.push(0);
                    break;
            case EQ:
                    b = operations.top();
                    operations.pop();

                    a = operations.top();
                    operations.pop();

                    if(a == b)
                        operations.push(1);
                    else
                        operations.push(0);
                    break;

            case JMP_FALSE:
                    x = operations.top();
                    if(x == 0)
                    {
                        line = ins.operand - 2;
                    }
                    break;

            case GOTO:
                    line = ins.operand - 2;
                    break;

            case STORE:
                    x = operations.top();
                    operations.pop();

                    dataSegment[ins.operand] = x;
                    break;

            case ADD:
                    b = operations.top();
                    operations.pop();

                    a = operations.top();
                    operations.pop();

                    operations.push(a + b);
                    break;

            case MUL:
                    b = operations.top();
                    operations.pop();

                    a = operations.top();
                    operations.pop();

                    operations.push(a * b);
                    break;

            case SUB:
                    b = operations.top();
                    operations.pop();

                    a = operations.top();
                    operations.pop();

                    operations.push(a - b);
                    break;

            case DIV:
                    b = operations.top();
                    operations.pop();

                    a = operations.top();
                    operations.pop();

                    operations.push(a / b);

                    break;

            case HALT:
                    exit(0);
                    break;
        }

        line++;

    }
    

    return 0;
}

int get_type(string type)
{
    if(type == "res")
        return RES;
    else if(type == "read")
        return READ;
    else if(type == "write")
        return WRITE;
    else if(type == "load_var")
        return LOAD_VAR;
    else if(type == "load_int")
        return LOAD_INT;
    else if(type == "lt")
        return LT;
    else if(type == "gt")
        return GT;
    else if(type == "eq")
        return EQ;
    else if(type == "jmp_false")
        return JMP_FALSE;
    else if(type == "goto")
        return GOTO;
    else if(type == "store")
        return STORE;
    else if(type == "add")
        return ADD;
    else if(type == "mul")
        return MUL;
    else if(type == "sub")
        return SUB;
    else if(type == "div")
        return DIV;
    else if(type == "halt")
        return HALT;
    else
        return -1;
}