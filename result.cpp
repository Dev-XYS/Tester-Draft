#include "result.h"

vector<contestant_result> results;

inline bool _contestant_result_cmp_(const contestant_result &x, const contestant_result &y)
{
	return x.total_score > y.total_score;
}

void show_results()
{
	sort(results.begin(), results.end(), _contestant_result_cmp_);
	for (int i = 0; i < contestant_count; i++)
	{
		cout << setw(20) << results[i].contestant_name << setw(5) << results[i].total_score << endl;
	}
}
