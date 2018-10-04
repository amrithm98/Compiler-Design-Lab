#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> precedenceTable(4, vector<int>(4,0));
map<char,int> opToId;

void operatorPrecedenceParse(string s)
{

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
}

int main()
{

    setup();

    string s;
    cin >> s;

    operatorPrecedenceParse(s);
    return 0;
}