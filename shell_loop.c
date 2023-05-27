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
 * shell_loop - This function runs the main loop of the shell program.
 * @app_name: Name of the app
 * @envp: Environment variables
 *
 * Return: The exit status of the shell program.
 */

int shell_loop(char *app_name, char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int status = 1, i;
	char *command, *saveptr;

	do {
		if (isatty(STDIN_FILENO))
		{
			_putchar('$');
			_putchar(' ');
		}
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		i = 0;
		while (line[i] != '\0' && (line[i] == ' '
					|| line[i] == '\t' || line[i] == '\n'))
			i++;
		if (line[i] == '\0')
			continue;
		command = _strtok_two(line, ";", &saveptr);
		while (command != NULL)
		{
			args = parse_line(command);
			status = execute(app_name, args, envp);
			free(args);
			command = _strtok_two(NULL, ";", &saveptr);
		}
	} while (status);
	free(line);
	free(command);
	return (EXIT_SUCCESS);
}
