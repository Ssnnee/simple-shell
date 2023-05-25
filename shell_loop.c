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
	int status, i;

	line = NULL;
	/* Run the shell loop */
	do {
		/* Print the prompt if stdin is a terminal */
		if (isatty(STDIN_FILENO))
		{
			_putchar('$');
			_putchar(' ');
		}

		/* Read a line from stdin */
		line = _getline();
		if (line == NULL)
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

		/* Parse the line into arguments */
		args = parse_line(line);

		/* Execute the command */
		status = execute(app_name, args, envp);
		free(args);
	} while (status);

	free(line);
	return (EXIT_SUCCESS);
}
