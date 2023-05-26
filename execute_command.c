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
	int status, exit_code;	

	cmd = NULL;
	/* Check for an empty command */
	if (args[0] == NULL || args[0][0] == '\0')
		return (1);
	if (_strcmp(args[0], "exit"))
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
	cmd = get_full_path(*(args + 0), envp);

	/* Check if the command exists */
	if (access(cmd, X_OK) == -1)
	{
		perror(app_name);
		return (1);
	}

	/* Use fork to come back on the shell after execution of cmd */
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(cmd, args, envp) == -1)
		{
			perror(app_name);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
	free(cmd);
	return (1);
}

