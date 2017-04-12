#include "result.h"
#include "command.h"
#include "config_file.h"
#include "test.h"
#include "where.h"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern void do_command(vector<string> command);

extern void cmd_load(vector<string> args);
extern void cmd_test(vector<string> args);
extern void cmd_score(vector<string> args);
extern void cmd_cc(vector<string> args);
