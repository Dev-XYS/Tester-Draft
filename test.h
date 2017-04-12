#include "contest.h"
#include "colour.h"
#include "memory.h"
#include "result.h"
#include "where.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>

using namespace std;

extern void start_test();
