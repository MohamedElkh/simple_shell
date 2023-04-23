 "shell.h"

/**
 * _removalhash - function to remove any after #
 * @loc: the character to be checked
 *
 * Return: nothing.
 */

void _removalhash(char *bf)
{
	int x;

	for (x = 0; bf[x] != '\0'; x++)
	{
		if (bf[x] == '#')
		{
			bf[x] = '\0';
			break;
		}
	}
}

/**
 * _takeline - function to read the input by user
 * 
 *
 * Return: the result.
 */

char *_takeline()
{
	char s = 0;
	int x, rdf, bfsize = BUF_SIZE;
	char *bf = malloc(bfsize);

	if (bf == NULL)
	{
		free(bf);
		return (NULL);
	}
	for (x = 0; s != EOF && s != '\n'; x++)
	{
		fflush(stdin);
		rdf = read(STDIN_FILENO, &s, 1);
		if (rdf == 0)
		{
			free(bf);
			exit(EXIT_SUCCESS);
		}
		bf[x] = s;
		if (bf[0] == '\n')
		{
			free(bf);
			return ("\0");
		}
		if (x >= bfsize)
		{
			bf = fre_locate(bf, bfsize, bfsize + 1);
			if (bf == NULL)
			{
				return (NULL);
			}
		}
	}
	bf[x] = '\0';
	_removalhash(bf);
	return (bf);
}
