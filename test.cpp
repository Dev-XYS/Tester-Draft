#include "test.h"

bool is_tle;
itimerval timer_info;

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

bool file_checker(string contestant_output_file, string standard_output_file)
{
	return system(("diff -w > /dev/null 2>&1 " + contestant_output_file + " " + standard_output_file).c_str()) == 0;
}

void test_contestant(string contestant_dir, string contestant_name)
{
	vector<int> scores;
	int total_score = 0;
	for (int i = 0; i < loaded_contest.problem_count; i++)
	{
		cout << "Problem: " << loaded_contest.problems[i].problem_name << endl;
		int problem_score = 0;
		if (system(("g++ src/" + contestant_dir + loaded_contest.problems[i].problem_name + ".cpp -o _tester_exe_").c_str()) != 0)
		{
			cout << endl;
			continue;
		}
		for (int j = loaded_contest.problems[i].testcase_begin; j <= loaded_contest.problems[i].testcase_end; j++)
		{
			cout << "Test for testcase #" << setw(2) << j << " ";
			fflush(stdout);
			timeval start_time, end_time;
			is_tle = false;
			system(("cp data/" + loaded_contest.problems[i].problem_name + "/" + (loaded_contest.problems[i].problem_name + j) + ".in " + loaded_contest.problems[i].problem_name + ".in").c_str());
			gettimeofday(&start_time, NULL);
			start_timer(loaded_contest.problems[i].time_limit);
			int return_value = system("./_tester_exe_ > /dev/null 2>&1");
			cancel_timer();
			gettimeofday(&end_time, NULL);
			if (get_last_memory_use() > loaded_contest.problems[i].memory_limit)
			{
				cout << RED("MLE") << endl;
			}
			else if (is_tle == true)
			{
				cout << RED("TLE") << endl;
			}
			else if (return_value != 0)
			{
				cout << RED("RE") << endl;
			}
			else
			{
				if (file_checker(loaded_contest.problems[i].problem_name + ".out", "data/" + loaded_contest.problems[i].problem_name + "/" + (loaded_contest.problems[i].problem_name + j) + loaded_contest.problems[i].answer_suffix) == true)
				{
					cout << GREEN("AC");
					problem_score += loaded_contest.problems[i].score_per_testcase;
				}
				else
				{
					cout << RED("WA");
				}
				cout << setw(6) << get_ms(start_time, end_time) << " ms" << endl;
			}
			system("rm _tester_temporary_output_file_ > /dev/null 2>&1");
		}
		total_score += problem_score;
		scores.push_back(problem_score);
		system("rm _tester_exe_ > /dev/null 2>&1");
		cout << endl;
	}
	results.push_back(contestant_result(contestant_name, scores, total_score));
}

void start_test()
{
	if (current_contestant == "")
	{
		system("ls src -F | grep / > _tester_contestant_list_");
		fstream fin("_tester_contestant_list_");
		string contestant_dir;
		string contestant_name;
		results.clear();
		contestant_count = 0;
		while (fin >> contestant_dir)
		{
			contestant_count++;
			contestant_name = contestant_dir;
			contestant_name[contestant_name.size() - 1] = '\0';
			cout << endl << ">>> Contestant: " << contestant_name << endl << endl;
			test_contestant(contestant_dir, contestant_name);
		}
		system("rm _tester_contestant_list > /dev/null 2>&1");
		system("rm _tester_memory_ > /dev/null 2>&1");
	}
	else
	{
		cout << endl << ">>> Contestant: " << current_contestant << endl << endl;
		test_contestant(current_contestant + "/", current_contestant);
	}
}
