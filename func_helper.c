#include "shell.h"

void handleline(char **lin, ssize_t ready);
ssize_t getnew_len(char *lin);
void logicalop(char *lin, ssize_t *new_len);

/**
 * handleline - func to Partitions a line read from standard input as needed.
 * @lin: line read from standard input.
 * @ready: length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 * Return: nothing.
 */

void handleline(char **lin, ssize_t ready)
{
	char previous, current, next;
	char *old, *new;
	unsigned int i, x;
	ssize_t new_len;

	new_len = getnew_len(*lin);
	if (new_len == ready - 1)
	{
		return;
	}
	new = malloc(new_len + 1);
	if (!new)
	{
		return;
	}
	x = 0;

	old = *lin;

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

	free(*lin);

	*lin = new;
}

/**
 * getnew_len - func to Gets the new length of a line partitioned
 * @lin: The line to check.
 * Description: Cuts short lines containing
 * Return: The new length of the line
 */

ssize_t getnew_len(char *lin)
{
	ssize_t new_l = 0;
	unsigned int x;
	char next, current;

	for (x = 0; lin[x]; x++)
	{
		current = lin[x];
		next = lin[x + 1];
		if (current == '#')
		{
			if (x == 0 || lin[x - 1] == ' ')
			{
				lin[x] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (current == ';')
			{
				if (next == ';' && lin[x - 1] != ' ' && lin[x - 1] != ';')
				{
					new_l += 2;

					continue;
				}
				else if (lin[x - 1] == ';' && next != ' ')
				{
					new_l += 2;
					continue;
				}
				if (lin[x - 1] != ' ')
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
				logicalop(&lin[x], &new_l);
			}
		}
		else if (current == ';')
		{
			if (x != 0 && lin[x - 1] != ' ')
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
 * logicalop - func to Checks a line for logical operator
 * @lin: the character to check in the line.
 * @new_len: new_len in get_new_len function.
 */

void logicalop(char *lin, ssize_t *new_len)
{
	char prev, current;
	char n;

	prev = *(lin - 1);

	current = *lin;

	n = *(lin + 1);

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
