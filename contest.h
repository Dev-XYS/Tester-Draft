#ifndef __CONTEST_H__

#define __CONTEST_H__

#include "problem.h"

#include <vector>
#include <string>

using namespace std;

struct contest
{
	string contest_name;
	int problem_count;
	vector<problem> problems;
};

extern contest loaded_contest;
extern int contestant_count;

#endif
