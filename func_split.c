#include "shell.h"


int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);
int token_len(char *str, char *delim);

/**
 * token_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */

int token_len(char *str, char *delim)
{
	int i = 0;
	int le = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		le++;
		i++;
	}

	return (le);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */

int count_tokens(char *str, char *delim)
{
	int x, tok = 0;
	int le = 0;

	for (x = 0; *(str + x); x++)
	{
		le++;
	}

	for (x = 0; x < le; x++)
	{
		if (*(str + x) != *delim)
		{
			tok++;
			x += token_len(str + x, delim);
		}
	}

	return (tok);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */

char **_strtok(char *line, char *delim)
{
	char **pt;
	int x = 0, tok, t;
	int letter, l;

	tok = count_tokens(line, delim);

	if (tok == 0)
	{
		return (NULL);
	}

	pt = malloc(sizeof(char *) * (tok + 2));

	if (!pt)
	{
		return (NULL);
	}

	for (t = 0; t < tok; t++)
	{
		while (line[x] == *delim)
		{
			x++;
		}

		letter = token_len(line + x, delim);

		pt[t] = malloc(sizeof(char) * (letter + 1));

		if (!pt[t])
		{
			for (x -= 1; x >= 0; x--)
			{
				free(pt[x]);
			}
			free(pt);
			return (NULL);
		}

		for (l = 0; l < letter; l++)
		{
			pt[t][l] = line[x];

			x++;
		}

		pt[t][l] = '\0';
	}
	pt[t] = NULL;

	pt[t + 1] = NULL;

	return (pt);
}
