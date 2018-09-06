#include <bits/stdc++.h>
using namespace std;

set<string> identifiers;

void parse(string s)
{

}

int main()
{

	ifstream in("input.txt");
	ofstream op("output.txt");

	string s;
	while(getline(in,s))
	{
		cout << s << endl;
		parse(s);
	}	
	return 0;	
}
