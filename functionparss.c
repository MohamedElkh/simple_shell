#include "shell.h"

/**
 * func_parse - function to parse line of input
 * @inp: the character to be checked
 *
 * Return: the result.
 */

char **func_pasre(char *inp)
{
	char *tok;
	char **toks;
	int bfsize = BUF_SIZE;
	int x;

	if (inp == NULL)
	{
		return (NULL);
	}
	toks = malloc(sizeof(char *) * bfsize);

	if (!toks)
	{
		perror("hsh");
		return (NULL);
	}
	tok = strtoken(inp, "\n ");

	for (x = 0; tok; x++)
	{
		toks[x] = tok;
		tok = strtoken(NULL, "\n ");
	}
	toks[x] = NULL;
	return (toks);
}
