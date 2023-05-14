#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
/**
 * execute - This function executes a command with the given arguments.
 * @args: The arguments for the command.
 *
 * Return: The exit status of the command.
 */
int execute(char **args)
{
	char *cmd;
	pid_t child_pid;
	int status;

	cmd = NULL;
	/* This for an empty command*/
	if (args[0] == NULL)
		return (1);
	if (args)
	{
		cmd = get_full_path(args[0]);

		/*Use fork to come back on the shell after execution of cmd*/
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(cmd, args, NULL) == -1)
			{
				perror(app_name);
			}
		}
		else
		{
			wait(&status);
		}
	}
	return (1);
}
