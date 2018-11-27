/**

Author  : Amrith M
Code    : RDP
INPUT   : input.txt

Grammar : Productions.txt
Logic   : Custom Function for Each Non Terminal is made

Execution : g++ rdp.cpp && ./a.out < input.txt

*/


#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

//string s is the input
string s;
//ptr is the position of the next symbol
int ptr = 0;
//error flag is set to 1 if there is error

int error = 0;

void A()
{
    if(s[ptr] == 'a')
    {
        ptr++;
        A();
        if(s[ptr] == 'b')
        {
            ptr++;
            return;
        }
        else
            error = 1;
    }
}

void B()
{   
    if(s[ptr] == 'c')
    {
        ptr++;
        B();
        if(s[ptr] == 'd')
        {
            ptr++;
            return;
        }
        else
            error = 1;
    }
    return;
}

void S()
{
    if(s.size() < 4)
    {
        error = 1;
        return;
    }
    A();
    if(error == 0)
        B();
    if(ptr != s.size())
        error = 1;
}

int main()
{
    ifstream infile("input.txt");

    string temp;

    //getline reads each line from input.txt , resets all parameters and parses
    while(getline(infile,temp))
    {
        error = 0;
        ptr = 0;

        cout << "\n" << temp;

        s = temp;

        S();

        if(error == 0)
            cout << "\tSuccessfully Parsed";
        else    
            cout << "\tError in Parsing";
    }
    

    return 0;
}