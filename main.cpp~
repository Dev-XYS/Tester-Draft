#include "command.h"
#include "commands.h"

int main()
{
	while (true)
	{
		prompt_main();
		vector<string> command = get_args();
		if (command.size() > 0)
		{
			do_command(command);
		}
	}
	return 0;
}
