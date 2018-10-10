#include <bits/stdc++.h>
#include "stack.h"
using namespace std;

vector<vector<int>> precedenceTable(4, vector<int>(4,0));
map<char,int> opToId;

bool operatorPrecedenceParse(string s)
{
    s += '$';

    Stack<char> st;
    st.push('$');

    int i = 0;

    while(i < s.size())
    {
        char b = st.top();
        char a = s[i];
        
        int prec_b = opToId[b];
        int prec_a = opToId[a];

        cout << "\nState : " << a << " " << b << " " << endl;

        if(b == '$' && a == '$')
        {
            return true;
        }

        st.print();

        if(precedenceTable[prec_a][prec_b] >= 1)
        {
            st.push(a);
            i++;
        }
        else
        {
            if(!st.empty())
            {
                char c = st.top();
                while(c != '$' && !st.empty() && precedenceTable[opToId[a]][opToId[c]] < 1)
                {
                    st.pop();
                    if(!st.empty())
                        c = st.top();
                }
            }
        }
    }

    return false;
}

void setup()
{
    opToId['i'] = 0;
    opToId['+'] = 1;
    opToId['*'] = 2;
    opToId['$'] = 3;

    precedenceTable[0][0] = 2;
    precedenceTable[0][1] = 1;
    precedenceTable[0][2] = 1;
    precedenceTable[0][3] = 1;

    precedenceTable[1][0] = 0;
    precedenceTable[1][1] = 1;
    precedenceTable[1][2] = 0;
    precedenceTable[1][3] = 1;

    precedenceTable[2][0] = 0;
    precedenceTable[2][1] = 1;
    precedenceTable[2][2] = 1;
    precedenceTable[2][3] = 1;

    precedenceTable[3][0] = 0;
    precedenceTable[3][1] = 0;
    precedenceTable[3][2] = 0;
    precedenceTable[3][3] = 2;
    
}

int main()
{

    setup();

    string s;
    cin >> s;

    cout << operatorPrecedenceParse(s);

    return 0;
}