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
	char *line;
	char **args;
	int status;

	do {
		/* Print the prompt */
		_putchar('$');
		_putchar(' ');

		/* Read a line from stdin */
		line = _getline();

		/* Parse the line into arguments */
		args = parse_line(line);

		/* Execute the command */
		status = execute(app_name, args, envp);

		free(line);
		free(args);
	} while (status);
	return (EXIT_SUCCESS);
}
