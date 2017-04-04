#ifndef __RESULT_H__

#define __RESULT_H__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct contestant_result
{
	string contestant_name;
	vector<int> scores;
	int total_score;
	contestant_result(string _contestant_name, vector<int> _scores, int _total_score) : contestant_name(_contestant_name), scores(_scores), total_score(_total_score) { }
};

extern int contestant_count;
extern vector<contestant_result> results;

extern void show_results();

#endif
