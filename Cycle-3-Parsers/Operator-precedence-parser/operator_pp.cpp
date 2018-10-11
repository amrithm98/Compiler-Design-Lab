#include <bits/stdc++.h>
using namespace std;

vector<char> st(100);
vector<string> handles;
vector<string> precedence(9);
string prevHandle;
int ptr;
int top;

int getOperatorIndex(char value)
{
    switch(value)
    {
        case '+':   
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '^':
            return 4;
        case 'i':
            return 5;
        case '(':
            return 6;
        case ')':
            return 7;
        case '$':
            return 8;
        default:
            return -1;
    }
}

void shift(char c)
{
    st[++top] = c;
    ptr++;
}

bool reduce()
{
    bool found;

    for(int i = 0; i < handles.size(); i++)
    {
        int size = handles[i].size();

        if(st[top] == handles[i][0] && top + 1 >= size )
        {  
            found = true;
            int j;
            for(j = 0; j < size; j++)
            {
                if(st[top - j] != handles[i][j])
                {
                    found = false;
                    break;
                }
            }

            if(found)
            {
                st[top - j + 1] = 'E';
                top = top - j + 1;
                prevHandle = handles[i];
                return true;
            }
        }
    }

    return false;
}

void setup()
{
    ptr = 0;
    st[0] = '$';
    handles = {"i", "E+E", "E*E", "E-E", "E^E", ")E("};
    top = 0;
    //Precedence Table
    precedence[0] = {'>', '>','<','<','<','<','<','>','>'};
    precedence[1] = {'>', '>','<','<','<','<','<','>','>'};
    precedence[2] = {'>', '>','>','>','<','<','<','>','>'};
    precedence[3] = {'>', '>','>','>','<','<','<','>','>'};
    precedence[4] = {'>', '>','>','>','<','<','<','>','>'};
    precedence[5] = {'>', '>','>','>','>','e','e','>','>'};
    precedence[6] = {'<', '<','<','<','<','<','<','>','e'};
    precedence[7] = {'>', '>','>','>','>','e','e','>','>'};
    precedence[8] = {'<', '<','<','<','<','<','<','<','>'};

}

void printStack()
{
    for(int i = 0; i < top+1; i++)
        cout << st[i];
}

bool operator_pp(string s)
{
    cout << "\nSTACK \tInput \tAction\n=======================\n";
    while(ptr < s.size())
    {
        shift(s[ptr]);
        printStack();
        cout << "\t" << s.substr(ptr);
        cout << "\t" << "Shift" << endl;

        int tp = getOperatorIndex(st[top]);
        int curr = getOperatorIndex(s[ptr]);

        if(precedence[tp][curr] == '>')
		{
            while(reduce())
            {
                printStack();
                cout << "\t" << s.substr(ptr);
                cout << "\tReduced : E->" << prevHandle << endl;
            }
        }

    }

    if(st.size() > 1 && st[0] == '$' && st[1] == 'E' && st[2] == '$')
        return true;

    return false;
}

int main()
{
    string s;
    cin >> s;

    s += '$';

    setup();

    if(operator_pp(s))
        cout << "\nSuccessfully Parsed\n";
    else    
        cout << "\nError in Expression\n";

    return 0;
}