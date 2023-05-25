#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * _read_input - This function reads input from
 * the standard input into a buffer.
 * @buf: The buffer to store the input.
 * @buf_size: The size of the buffer.
 *
 * Return: The number of characters read from the standard input.
 */
ssize_t _read_input(char *buf, size_t buf_size)
{
	ssize_t n_read;

	n_read = read(STDIN_FILENO, buf, buf_size);
	if (n_read < 0)
		exit(EXIT_FAILURE);
	return (n_read);
}

/**
 * _get_line_from_buf - This function extracts a line of input from a buffer.
 * @buf: The buffer containing the input.
 * @buf_pos: The current position in the buffer.
 * @buf_size: The size of the buffer.
 * @line: The line extracted from the buffer.
 * @line_pos: The current position in the line.
 * @line_size: The size of the line.
 *
 * Return: 1 if a line was extracted from the buffer, 0 otherwise.
 */
int _get_line_from_buf(char *buf, int *buf_pos,
		int buf_size, char **line, int *line_pos, int *line_size)
{
	int i;

	while (*buf_pos < buf_size)
	{
		if (buf[*buf_pos] == '\n' || buf[*buf_pos] == EOF)
		{
			(*buf_pos)++;
			(*line)[*line_pos] = '\0';
			return (1);
		}
		else
		{
			if (*line_pos >= *line_size)
			{
				char *new_line;
				*line_size += MAX_LINE;

				new_line = malloc(*line_size);
				if (new_line == NULL)
					exit(EXIT_FAILURE);
				if (*line != NULL)
				{
					for (i = 0; i < *line_pos; i++)
						new_line[i] = (*line)[i];
					free(*line);
				}
				*line = new_line;
			}
			(*line)[(*line_pos)++] = buf[(*buf_pos)++];
		}
	}
	return (0);
}
/**
 * _getline - This function reads a line from standard input.
 *
 * Return: A pointer to the line read from standard input.
 */
char *_getline(void)
{
	static char buf[MAX_LINE];
	static int buf_pos, buf_size;
	char *line;
	int line_pos, line_size;

	buf_pos = 0, buf_size = 0, line_pos = 0, line_size = 0, line = NULL;

	while (1)
	{
		if (buf_pos >= buf_size)
		{
			buf_size = _read_input(buf, MAX_LINE);
			if (buf_size == 0)
				return ((line_size == 0) ? NULL : (line[line_pos] = '\0', line));
			buf_pos = 0;
		}

		if (_get_line_from_buf(buf, &buf_pos, buf_size, &line,
					&line_pos, &line_size))
			return (line);
	}
}
