#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strtok - breaks a string into a series of tokens using delimiters
 * @str: string to tokenize
 * @delimiters: array of delimiters
 *
 * Return: string token
 */
char *_strtok(char *str, char *delimiters)
{
	static char *tmp_str;
	char *token;
	int found;

	/* first time call */
	if (str != NULL)
		tmp_str = str;
	else if (tmp_str == NULL || *tmp_str == '\0')
		return (NULL);

	/* end of string */
	if (tmp_str == NULL)
		return (NULL);

	/* Skip leading spaces */
	while (find_char(*tmp_str, delimiters))
		tmp_str++;

	token = tmp_str;
	found = 0;
	while (*tmp_str)
	{
		if (find_char(*tmp_str, delimiters))
		{
			*tmp_str = '\0';
			tmp_str++;
			found = 1;
			break;
		}
		tmp_str++;
	}
	if (found != 1)
		tmp_str = NULL;

	return (token);
}

/**
 * find_char - checks if a character is in a string
 * @str: The string
 * @c: the character
 *
 * Return: 0 if not found and 1 if found
 */
int find_char(char c, char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

