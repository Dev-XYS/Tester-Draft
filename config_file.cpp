#include "config_file.h"

string config_filename;

void load_config_file(string filename)
{
	fstream fin(filename.c_str());
	config_filename = filename;
	fin >> loaded_contest.contest_name;
	fin >> loaded_contest.problem_count;
	loaded_contest.problems.resize(loaded_contest.problem_count);
	for (int i = 0; i < loaded_contest.problem_count; i++)
	{
		fin >> loaded_contest.problems[i].problem_name >> loaded_contest.problems[i].testcase_begin >> loaded_contest.problems[i].testcase_end >> loaded_contest.problems[i].score_per_testcase >> loaded_contest.problems[i].time_limit >> loaded_contest.problems[i].memory_limit >> loaded_contest.problems[i].answer_suffix;
	}
	prompt_contest_name = loaded_contest.contest_name;
}
