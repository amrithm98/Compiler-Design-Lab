/**
 * Author : Amrith M
 * This code tokenizes the given program and prints what each token is
 * This code is written in c++ and uses regex library
 * regex_match is used to match regexp with string
 * 
 * 
 * */
#include <bits/stdc++.h>
using namespace std;

set<string> keywords = {"prog" , "begin" , "end" , "if" , "then" , "else" , "endif" , "while" , "do" , "endwhile" , "read" , "write", "integer" };
set<string> operators = { ":=" , "+" , "-" , "*" , "/" , "=" , "<" , ">" };
set<char> symbols = { '.', ',', '(', ')'};
set<char> ops = {':','+','-','*','/','<','>',';',','};

regex identifier("[a-zA-Z_][_a-zA-Z0-9]*");
regex digits("[1-9][0-9]*");

vector< pair<string,string> > tokens;

vector<string> splitDelimiter(string s, char ch)
{
	stringstream ss(s);
	vector<string> arr;

	while(ss)
	{
		string temp;
		if(getline(ss,temp,ch))
		{
			arr.push_back(temp);
		}
		else
			break;
	}

	return arr;

}

bool putMatching(string current)
{
	if(keywords.find(current) != keywords.end())
	{
		tokens.push_back({"keyword",current});
		return true;
	}

	if(operators.find(current) != operators.end())
	{
		tokens.push_back({"operator",current});
		return true;
	}

	if(regex_match(current,identifier))
	{
		tokens.push_back({"identifier",current});
		return true;
	}

	if(regex_match(current,digits))
	{
		tokens.push_back({"literal",current});
		return true;
	}

	return false;
}

string stripStr(string stripString)
{
	while(!stripString.empty() && std::isspace(*stripString.begin()))
    	stripString.erase(stripString.begin());

	while(!stripString.empty() && std::isspace(*stripString.rbegin()))
    	stripString.erase(stripString.length()-1);

	return stripString;
}

void parse(string s)
{
	vector<string> spaceSplit = splitDelimiter(s,' ');
	vector<string> strings;

	for(auto it : spaceSplit)
	{
		vector<string> temp = splitDelimiter(it,';');
		strings.insert(strings.end(),temp.begin(),temp.end());
	}

	for(int i = 0; i < strings.size(); i++)
	{
		string current = strings[i];
		current = stripStr(current);

		if(!putMatching(current))
		{
			int left = 0, right = 0;
			string temp = "";
			while(right < current.size() && left <= right)
			{
				if(symbols.find(current[right]) != symbols.end())
				{
					putMatching(temp);
					temp = "";
					tokens.push_back({"symbol",string(1,current[right])});
					putMatching(current.substr(left,right-left+1));
					left = right+1;
					right++;
					continue;
				}
				else if(ops.find(current[right]) != ops.end())
				{
					putMatching(temp);
					temp = "";
					if(current[right] == ':')
					{
						tokens.push_back({"operator",":="});
						putMatching(current.substr(left,right-left));
						left = right+2;
						right += 2;
					}
					else
					{
						tokens.push_back({"operator",string(1,current[right])});
						putMatching(current.substr(left,right-left));
						left = right+1;
						right++;
					}
					continue;
				}
				else
				{
					temp += current[right];
					right++;
				}
			}
			if(right >= left)
			{
				putMatching(current.substr(left,right-left));
			}
		}	
	}
}

int main()
{

	ifstream in("input.txt");
	ofstream op("output.txt");

	string s;
	while(getline(in,s))
	{
		parse(s);
	}	

	for(auto it : tokens)
	{
		cout << setw(12) << it.first << " : " << it.second << endl;
	}

	return 0;	
}
