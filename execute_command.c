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
 * @app_name: Name of the application
 * @args: The arguments for the command.
 * @envp: Environment variables pointer
 *
 *
 * Return: The exit status of the command.
 */
int execute(char *app_name, char **args, char **envp)
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
		/*Handle exit cmd */
		if (_strcmp(args[0], "exit"))
			exit(0);
		cmd = get_full_path(args[0]);
		/*Use fork to come back on the shell after execution of cmd*/
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(cmd, args, envp) == -1)
			{
				char *error_msg, *not_found_msg;
				int i;

				error_msg = app_name;
				for (i = 0; error_msg[i] != '\0'; i++)
					_putchar(error_msg[i]);
				_putchar(':');
				_putchar(' ');
				for (i = 0; args[0][i] != '\0'; i++)
					_putchar(args[0][i]);

				not_found_msg = ": not found\n";
				for (i = 0; not_found_msg[i] != '\0'; i++)
					_putchar(not_found_msg[i]);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	} return (1);
}
