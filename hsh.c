#include "hsh.h"
#include <stdlib.h>
/**
 * main - The main function of the shell program.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings containing the arguments passed to the program.
 * @envp: Environment variables pointer
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char **argv, char **envp)
{
	/* Suppress unused parameter warnings */
	(void)argc;
	(void)argv;

	/* Run the shell loop */
	return (shell_loop(argv[0], envp));
}
/**
 * _putchar - This function writes a character to stdout.
 * @c: The character to be written.
 *
 * Return: On success, the number of characters written.
 * On error, -1 is returned.
 */
int _putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * get_full_path - this function gets the full path
 * of the command
 * @cmd: string of the command
 *
 * Return: full path of the cmd
 */
char *get_full_path(char *cmd)
{
	int i = 0, found = 0, j = 0;
	char *new_cmd;

	while (cmd[i] != '\0')
	{
		/* if the character / is found we assume that it's*/
		/* already full path*/
		if (cmd[i] == '/')
		{
			found = 1;
			break;
		}
		i++;
	}
	if (found)
		return (cmd);

	/* i already contains the size of initial cmd*/
	 /* we add 5 for '/bin/ */
	new_cmd = malloc(sizeof(char) * (i + 5));
	new_cmd[0] = '/';
	new_cmd[1] = 'b';
	new_cmd[2] = 'i';
	new_cmd[3] = 'n';
	new_cmd[4] = '/';

	while (j < i)
	{
		*(new_cmd + 5 + j) = *(cmd + j);
		j++;
	}
	return (new_cmd);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: 1 if equal, 0 otherwise
 */
int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
