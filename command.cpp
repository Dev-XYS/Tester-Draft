#include "command.h"

string prompt_base_string = "Tester";
string prompt_contest_name;
string prompt_contestant;
string prompt_problem;
string prompt_end = "~";

void prompt_main()
{
	cout << prompt_base_string;
	if (prompt_contest_name != "")
	{
		cout << ":" << prompt_contest_name;
		if (prompt_contestant != "")
		{
			cout << "@" << prompt_contestant;
		}
		if (prompt_problem != "")
		{
			cout << "@" << prompt_problem;
		}
	}
	cout << prompt_end;
}

vector<string> get_args()
{
	string command;
	stringstream stream;
	getline(cin, command);
	stream << command;
	vector<string> result;
	string arg;
	while (stream >> arg)
	{
		result.push_back(arg);
	}
	return result;
}
