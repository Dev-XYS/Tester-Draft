#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>

#define RED(...) (string)"\033[31m" + __VA_ARGS__ + (string)"\033[0m"
#define GREEN(...) (string)"\033[32m" + __VA_ARGS__ + (string)"\033[0m"
#define MAGENTA(...) (string)"\033[35m" + __VA_ARGS__ + (string)"\033[0m"
#define CYAN(...) (string)"\033[36m" + __VA_ARGS__ + (string)"\033[0m"

using namespace std;

itimerval timer_info;
bool is_tle;

string operator + (string, int);

void cmd_default();
void cmd_barebone();
void cmd_compile(string);
void cmd_debug(string);
void cmd_fundamental_test(string, int, int, int);
void cmd_create_data(string, string, int, int);
void cmd_create_answer(string, int, int);

int main()
{
	string cmd;
	stringstream in;
	while (true)
	{
		cout << CYAN("Tester~");
		getline(cin, cmd);
		in.clear();
		in.str("");
		in << cmd;
		in >> cmd;
		if (cmd == "")
		{
		}
		else if (cmd == "default")
		{
			cmd_default();
		}
		else if (cmd == "sleep")
		{
			int second;
			in >> second;
			sleep(second);
		}
		else if (cmd == "factor")
		{
			int number;
			in >> number;
			system(((string)"factor " + number).c_str());
		}
		else if (cmd == "exit")
		{
			break;
		}
		else if (cmd == "barebone")
		{
			cmd_barebone();
		}
		else if (cmd == "compile")
		{
			string filename;
			in >> filename;
			cmd_compile(filename);
		}
		else if (cmd == "debug")
		{
			string problem_name;
			in >> problem_name;
			cmd_debug(problem_name);
		}
		else if (cmd == "fundamental_test" || cmd == "ft")
		{
			string problem_name;
			int start_ord, end_ord, time_limit;
			in >> problem_name >> start_ord >> end_ord >> time_limit;
			cmd_fundamental_test(problem_name, start_ord, end_ord, time_limit);
		}
		else if (cmd == "create_data" || cmd == "cr")
		{
			string input_name, generator_name;
			int para1, para2;
			in >> input_name >> generator_name >> para1 >> para2;
			cmd_create_data(input_name, generator_name, para1, para2);
		}
		else if (cmd == "create_answer" || cmd == "ca")
		{
			string problem_name;
			int start_ord, end_ord;
			in >> problem_name >> start_ord >> end_ord;
			cmd_create_answer(problem_name, start_ord, end_ord);
		}
		else
		{
			cout << "command " << MAGENTA(cmd) << " does not exist" << endl;
		}
	}
	return 0;
}

string operator + (string s, int n)
{
	if (n == 0)
	{
		return s + '0';
	}
	int i = 0;
	char res[10];
	while (n > 0)
	{
		res[i++] = n % 10 + '0';
		n /= 10;
	}
	for (i--; i >= 0; i--)
	{
		s += res[i];
	}
	return s;
}

void cmd_default()
{
}

void cmd_barebone()
{
	cout << "program return " << system("./a.out") << endl;
}

void cmd_compile(string filename)
{
	system(("g++ " + filename).c_str());
}

void timer_tick_proc(int timer_ord)
{
	is_tle = true;
	system("pkill _tester_exe_");
}

void start_timer(int tick_time)
{
	timeval first_tick, interval;
	first_tick.tv_sec = tick_time / 1000;
	first_tick.tv_usec = tick_time % 1000 * 1000;
	interval.tv_sec = 0;
	interval.tv_usec = 0;
	timer_info.it_value = first_tick;
	timer_info.it_interval = interval;
	signal(SIGALRM, timer_tick_proc);
	setitimer(ITIMER_REAL, &timer_info, NULL);
}

void cancel_timer()
{
	timer_info.it_value.tv_sec = 0;
	timer_info.it_value.tv_usec = 0;
}

void clear_line()
{
	cout << "\033[1A\033[22C\033[K";
}

int get_ms(timeval &start, timeval &end)
{
	return (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}

bool file_checker(string standard_output_file)
{
	return system(("diff -w > /dev/null 2>&1 _tester_temporary_output_file_ " + standard_output_file).c_str()) == 0;
}

void cmd_debug(string problem_name)
{
	system(("g++ " + problem_name + ".cpp -o _tester_exe_").c_str());
	timeval start_time, end_time;
	is_tle = false;
	gettimeofday(&start_time, NULL);
	start_timer(1000);
	int return_value = system(("./_tester_exe_ < " + problem_name + ".in > _tester_temporary_output_file_").c_str());
	cancel_timer();
	gettimeofday(&end_time, NULL);
	if (is_tle == true)
	{
		clear_line();
		cout << RED("TLE") << endl;
	}
	else if (return_value != 0)
	{
		clear_line();
		cout << RED("RE") << endl;
	}
	else
	{
		if (file_checker(problem_name + ".ans") == true)
		{
			cout << GREEN("AC") << endl;
		}
		else
		{
			cout << RED("WA") << endl;
		}
	}
}

void cmd_fundamental_test(string problem_name, int start_order, int end_order, int time_limit)
{
	cout << "compiling..." << endl;
	system(("g++ src/" + problem_name + ".cpp -o _tester_exe_").c_str());
	for (int i = start_order; i <= end_order; i++)
	{
		cout << "test for testcase #" << setw(2) << i << " ";
		fflush(stdout);
		timeval start_time, end_time;
		is_tle = false;
		gettimeofday(&start_time, NULL);
		start_timer(time_limit);
		int return_value = system(("./_tester_exe_ < data/" + (problem_name + i) + ".in > _tester_temporary_output_file_").c_str());
		cancel_timer();
		gettimeofday(&end_time, NULL);
		if (is_tle == true)
		{
			clear_line();
			cout << RED("TLE") << endl;
		}
		else if (return_value != 0)
		{
			clear_line();
			cout << RED("RE") << endl;
		}
		else
		{
			if (file_checker("data/" + (problem_name + i) + ".ans") == true)
			{
				cout << GREEN("AC");
			}
			else
			{
				cout << RED("WA");
			}
			cout << setw(6) << get_ms(start_time, end_time) << " ms" << endl;
		}
	}
	system("rm _tester_exe_");
	system("rm _tester_temporary_output_file_");
}

void cmd_create_data(string input_name, string generator_name, int para1, int para2)
{
	system(("data/" + generator_name + " " + para1 + " " + para2 + " > data/" + input_name).c_str());
}

void cmd_create_answer(string problem_name, int start_ord, int end_ord)
{
	for (int i = start_ord; i <= end_ord; i++)
	{
		system(("src/std < data/" + (problem_name + i) + ".in > data/" + (problem_name + i) + ".ans").c_str());
	}
}
