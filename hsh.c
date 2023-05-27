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
 * main - The main function of the shell program.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings containing the arguments passed to the program.
 * @envp: Environment variables pointer
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char **argv, char **envp)
{ int fd;
	char buf[MAX_LINE];
	ssize_t nread, i;
	char *line, *new_line, **args;
	size_t line_size, j;

	line = NULL, line_size = 0;
	if (argc > 1)
	{
		if (_strcmp(argv[1], "env"))
			return (_printenv(envp));
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{ perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		while ((nread = read(fd, buf, MAX_LINE)) > 0)
		{
			for (i = 0; i < nread; i++)
			{
				if (buf[i] == '\n')
				{ args = parse_line(line);
					execute(argv[0], args, envp);
					my_free_args(args), free(line);
					line = NULL, line_size = 0;
				}
				else
				{ new_line = malloc(line_size + 2);
					for (j = 0; j < line_size; j++)
						new_line[j] = line[j];
					new_line[line_size++] = buf[i];
					new_line[line_size] = '\0';
					free(line);
					line = new_line;
				}
			}
		} close(fd);
		free(line);
		exit(EXIT_SUCCESS);
	} return (shell_loop(argv[0], envp));
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
 * @envp: environment pointer
 *
 * Return: full path of the cmd
 */
char *get_full_path(char *cmd, char **envp)
{
	int i = 0, found = 0;

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

	return (get_path(cmd, envp));
}

/**
 * get_path - gets the path based on the command
 * @cmd: command
 * @envp: environment pointer
 *
 * Return: full path if found and the cmd itself otherwise
 */
char *get_path(char *cmd, char **envp)
{
	char *path;
	char *dir;
	int i = 0;
	char dirFull[1024];
	char *path_copy, *slash = "/";

	/* Search for PATH var in envp*/
	while (_strncmp(envp[i], "PATH=", 5) == 0)
		i++;

	path = envp[i];
	path_copy = make_path_copy(path);
	dir = strtok(path_copy, "=");
	dir = strtok(NULL, ":");

	while (dir != NULL)
	{
		_memset(dirFull, 0, 1024);
		_strcpy(dirFull, dir);
		if (access(_strcat(_strcat(dirFull, slash), cmd), F_OK) == 0)
		{
			free(path_copy);
			return (_strdup(dirFull));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (cmd);
}

/**
 * make_path_copy - makes a copy of path for manipulations
 * @path: environment variables =
 *
 * Return: a copy of path
 */
char *make_path_copy(char *path)
{
	char *path_copy;

	path_copy = malloc(sizeof(char) * (_strlen(path) + 1));

	_strcpy(path_copy, path);
	return (path_copy);
}
