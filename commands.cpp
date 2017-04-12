#include "commands.h"

void do_command(vector<string> command)
{
	if (command[0] == "exit")
	{
		exit(0);
	}
	else if (command[0] == "load")
	{
		cmd_load(command);
	}
	else if (command[0] == "test")
	{
		cmd_test(command);
	}
	else if (command[0] == "score")
	{
		cmd_score(command);
	}
	else if (command[0] == "cc")
	{
		cmd_cc(command);
	}
	else
	{
		cout << "Command not found." << endl;
	}
}

void args_count_error(string command, int args_count)
{
	cout << "Command '" << command << "' does not take " << args_count << " argument(s)." << endl;
}

void cmd_load(vector<string> args)
{
	if (args.size() != 2)
	{
		args_count_error(args[0], args.size() - 1);
		return;
	}
	load_config_file(args[1]);
}

void cmd_test(vector<string> args)
{
	if (args.size() != 1)
	{
		args_count_error(args[0], args.size() - 1);
		return;
	}
	start_test();
}

void cmd_score(vector<string> args)
{
	if (args.size() != 1)
	{
		args_count_error(args[0], args.size() - 1);
		return;
	}
	show_results();
}

void cmd_cc(vector<string> args)
{
	if (args.size() > 2)
	{
		args_count_error(args[0], args.size() - 1);
		return;
	}
	if (args.size() == 1)
	{
		current_contestant = "";
		prompt_contestant = "";
	}
	else
	{
		current_contestant = args[1];
		prompt_contestant = args[1];
	}
}
