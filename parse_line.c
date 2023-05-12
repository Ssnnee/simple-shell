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
 * parse_line - This function parses a line of input into
 * an array of arguments.
 * @line: The line of input to be parsed.
 *
 * Return: An array of arguments.
 */
char **parse_line(char *line)
{
	char **args;
	char *arg;
	int i;

	/*The MAX_ARGS is just a buffer; like in the prevous project*/
	args = malloc(MAX_ARGS * sizeof(char *));
	if (!args)
	{
		perror("Could not allocate");
		exit(EXIT_FAILURE);
	}

	i = 0;
	/* " \t\n" Delimiters used to separate arguments*/
	while ((arg = strtok(i == 0 ? line : NULL, " \t\n")) != NULL)
	{
		args[i++] = arg;
		if (i == MAX_ARGS)
		{
			perror("Too many arguments");
			exit(EXIT_FAILURE);
		}
	}
	args[i] = NULL;
	return (args);
}
