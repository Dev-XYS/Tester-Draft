#ifndef __PROBLEM_H__

#define __PROBLEM_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct problem
{
	string problem_name;
	int testcase_begin, testcase_end, score_per_testcase, time_limit, memory_limit;
	string answer_suffix;
};

#endif
