#include "hsh.h"
#include <stdlib.h>

/**
 * _memset - Fills memory with a constant byte
 * @s: byte of memory pointed
 * @b: constant byte
 * @n: number of bytes
 *
 * Return: pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		*(s + i) = b;
		i++;
	}
	return (s);
}
/**
 * _strdup - create a pointer from a string array
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(char *str)
{
	char *dup;
	int i, len = 0;

	if (!str)
		return (NULL);

	while (str[len] != '\0')
	{
		len++;
	}

	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = str[i];
	dup[i] = '\0';

	return (dup);
}

/**
 * _printenv - prints the environment
 * @envp: env pointer variable
 *
 * Return: status
 */
int _printenv(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		write(STDOUT_FILENO, envp[i], _strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * my_exit - exits the program
 * @args: arguments
 * @cmd: command
 * @envp: environment pointer
 *
 * Return: void
 */
void my_exit(char **args, char *cmd, char **envp)
{
	int exit_code;

	envp = NULL;
	free(envp);
	free(cmd);
	if (args[1] == NULL)
	{
		my_free_args(args);
		_exit(EXIT_SUCCESS);
	}
	else
	{
		exit_code = _atoi(args[1]);
		my_free_args(args);
		_exit((exit_code >= 0 && exit_code <= 255) ? exit_code : exit_code % 256);
	}
}

/**
 * my_free_args - frees args variable
 * @args: var to free
 *
 * Return: void
 */
void my_free_args(char **args)
{
	int i = 0;

	while (args[i])
		free(args[i++]);
	free(args);
}
