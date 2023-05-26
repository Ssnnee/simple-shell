#include "hsh.h"

/**
 * _exit - implements exit built-in command
 * @args: arguments
 *
 * Return: void
 */
void _exit(char **args)
{
	if (args[1] == NULL)
	{
		free(args);
		exit(0);
	}
	else
	{
		exit_code = _atoi(args[1]);
		free(args);
		exit(exit_code);
	}
}
