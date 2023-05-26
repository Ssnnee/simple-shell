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
	char *line, *new_line;
	size_t line_size, j;
	char **args;

	line = NULL, line_size = 0;
	if (argc > 1)
	{
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
					free(args);
					free(line);
					line = NULL;
					line_size = 0;
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

/**
 * _strncmp - compares the first n characters of a string
 * @str1: first string
 * @str2: second string
 * @n: number of chars to compare
 *
 * Return: 1 if equal, 0 otherwise
 */
int _strncmp(char *str1, char *str2, int n)
{
	int i = 0;

	while (i < n)
	{
		if (*(str1 + i) != *(str2 + i))
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strcat - Concatenate two strings
 * @dest: Destination string
 * @src: string to append
 * Return: pointer to string dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;
	
	printf("dest : %p\n", dest);
	printf("src: %p\n", src);

	while (*(dest + i) != '\0')
	{
		i++;
	}

	while (*(src + j) != '\0')
	{
		*(dest + i) = *(src + j);
		j++;
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

/**
 * _strlen - function that returns the length of a string
 * @s: pointer to string value
 * Return: int (length of the string)
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _strcpy - copies the content of a array to another
 * @dest: destination array
 * @src: source array
 * Return: char pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
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
	char *dir, *dirFull;
	int i = 0;
	char *path_copy;
	
	/* Search for PATH var in envp*/
	while (_strncmp(envp[i], "PATH=", 5) == 0)
		i++;

	path = envp[i];
	path_copy = make_path_copy(path);
	dir = strtok(path_copy, "=");
	dir = strtok(NULL, ":");

	while (dir != NULL)
	{
		dirFull = malloc(sizeof(char) * (_strlen(dir) + 1 + _strlen(cmd)));
		_strcpy(dirFull, dir);
		dirFull = _strcat(_strcat(dirFull, "/"), cmd);
		if (access(dirFull, F_OK) == 0)
		{
			return (dirFull);
		}
		free(dirFull);
		dir = strtok(NULL, ":");
	}
	return (cmd);
}

/**
 * make_path_copy - makes a copy of path for manipulations
 * @envp: environment variables =
 *
 * Return: a copy of path
 */
char *make_path_copy(char *path)
{
	char *path_copy;
	path_copy = malloc(sizeof(char) * (strlen(path) + 1));

	strcpy(path_copy, path);
	return (path_copy);
}
