#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char previous, current, next;
	char *old, *new;
	unsigned int i, x;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
	{
		return;
	}
	new = malloc(new_len + 1);
	if (!new)
	{
		return;
	}
	x = 0;

	old = *line;
	for (i = 0; old[i]; i++)
	{
		current = old[i];

		next = old[i + 1];

		if (i != 0)
		{
			previous = old[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new[x++] = ' ';
					new[x++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new[x++] = ';';
					new[x++] = ' ';

					continue;
				}
				if (previous != ' ')
				{
					new[x++] = ' ';
				}

				new[x++] = ';';

				if (next != ' ')
				{
					new[x++] = ' ';
				}
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
				{
					new[x++] = ' ';
				}
				else if (previous == '&' && next != ' ')
				{
					new[x++] = '&';
					new[x++] = ' ';

					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
				{
					new[x++]  = ' ';
				}
				else if (previous == '|' && next != ' ')
				{
					new[x++] = '|';

					new[x++] = ' ';

					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old[i - 1] != ' ')
			{
				new[x++] = ' ';
			}
			new[x++] = ';';

			if (next != ' ' && next != ';')
			{
				new[x++] = ' ';
			}
			continue;
		}
		new[x++] = old[i];
	}

	new[x] = '\0';

	free(*line);

	*line = new;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	ssize_t new_l = 0;
	unsigned int x;
	char next, current;

	for (x = 0; line[x]; x++)
	{
		current = line[x];
		next = line[x + 1];
		if (current == '#')
		{
			if (x == 0 || line[x - 1] == ' ')
			{
				line[x] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[x - 1] != ' ' && line[x - 1] != ';')
				{
					new_l += 2;

					continue;
				}
				else if (line[x - 1] == ';' && next != ' ')
				{
					new_l += 2;
					continue;
				}
				if (line[x - 1] != ' ')
				{
					new_l++;
				}
				if (next != ' ')
				{
					new_l++;
				}
			}
			else
			{
				logical_ops(&line[x], &new_l);
			}
		}
		else if (current == ';')
		{
			if (x != 0 && line[x - 1] != ' ')
			{
				new_l++;
			}
			if (next != ' ' && next != ';')
			{
				new_l++;
			}
		}
		new_l++;
	}
	return (new_l);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char prev, current;
	char n;

	prev = *(line - 1);

	current = *line;
	n = *(line + 1);

	if (current == '&')
	{
		if (n == '&' && prev != ' ')
		{
			(*new_len)++;
		}
		else if (prev == '&' && n != ' ')
		{
			(*new_len)++;
		}
	}
	else if (current == '|')
	{
		if (n == '|' && prev != ' ')
		{
			(*new_len)++;
		}
		else if (prev == '|' && n != ' ')
		{
			(*new_len)++;
		}
	}
}
