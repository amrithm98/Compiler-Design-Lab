/**
 * Grammar Avoiding Left Recursion
 * 
 *  E -> TE'
 *  E' -> +TE' | ε
 *  T -> FT'
 *  T' -> *FT' | ε
 *  F -> (E) | id
**/


#include <bits/stdc++.h>
using namespace std;

string s;
int ptr = 0;
int error = 0;

void E();
void T();
void TDash();
void EDash();
void F();

void T()
{
    F();
    TDash();
}

void E()
{
    T();
    EDash();
}

void EDash()
{
    if(s[ptr] == '+')
    {
        ptr++;
        T();
        EDash();
    } 
}

void TDash()
{
    if(s[ptr] == '*')
    {
        ptr++;
        F();
        TDash();
    }
}

void F()
{
    if(isalnum(s[ptr]))
    {
        ptr++;
    }
    else if(s[ptr] == '(')
    {
        ptr++;
        E();
        if(s[ptr] == ')')
        {
            ptr++;
        }
        else
            error = 1;
    }
    else
        error = 1;
}

bool RDP()
{
    E();
    if(ptr == s.size() && error == 0)
        return true;
    else    
        return false;
}

int main()
{
    cin >> s;

    if(RDP())
    {
        cout << "\nSuccessfully Parsed Expression\n";
    }
    else
    {
        cout << "\nError Found In Expression\n";
    }

    return 0;
}