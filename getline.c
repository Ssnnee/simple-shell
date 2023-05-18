#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _getline - This function reads a line from standard input.
 *
 * Return: A pointer to the line read from standard input.
 * NULL if end of file is reached or an error occurs.
 */
char *_getline(void)
{ static char buf[MAX_LINE];
	static int buf_pos, buf_size;
	char *line;
	int line_pos, line_size;

	buf_pos = 0, buf_size = 0, line_pos = 0, line_size = 0;
	line = NULL;
while (1)
{
	if (buf_pos >= buf_size)
	{ buf_size = read(STDIN_FILENO, buf, MAX_LINE);
		if (buf_size == 0)
		{
			if (line_size == 0)
				return (NULL);
			else
			{ line[line_pos] = '\0';
				return (line);
			}
		}
		if (buf_size < 0)
			exit(EXIT_FAILURE);
	}
	while (buf_pos < buf_size)
	{
		if (buf[buf_pos] == '\n')
		{ buf_pos++;
			line[line_pos] = '\0';
			return (line);
		}
		else
		{
			if (line_pos >= line_size)
			{ char *new_line;
				line_size += MAX_LINE;
				new_line = malloc(line_size);
				if (new_line == NULL)
					exit(EXIT_FAILURE);
				if (line != NULL)
				{
					for (int i = 0; i < line_pos; i++)
						new_line[i] = line[i];
					free(line);
				} line = new_line;
			}
			line[line_pos++] = buf[buf_pos++];
		}
	}
}
}
