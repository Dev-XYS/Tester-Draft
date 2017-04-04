#include "memory.h"

int get_last_memory_use()
{
	system("ps -o rss,cmd | grep ./_tester_exe_ | tail -2 > _tester_memory_");
	fstream fin("_tester_momory_");
	int memory_use;
	fin >> memory_use;
	return memory_use;
}
