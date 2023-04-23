#include "shell.h"

/**
 * _envget - function to get the value of environment
 * @str: the character to be checked
 * Return: the result.
 */

char *_envget(char *str)
{
	char *val;
	unsigned int num, vv;
	int x, i, a;

	num = _stringlength(str);

	for (i = 0; environment[i]; i++)
	{
		if (strncompare(str, environment[i], num) == 0)
		{
			vv = _stringlength(environment[i]) - num;
			val = malloc(sizeof(char) * vv);

			if (!val)
			{
				free(val);
				perror("unable to alloc");
				return (NULL);
			}
			a = 0;
			for (x = num + 1; environment[i][x]; x++, a++)
			{
				val[a] = environment[i][x];
			}
			val[a] = '\0';
			return (val);
		}
	}
	return (NULL);
}

/**
 * *p_build - function to build command
 * @val: the character to be checked
 * @tok: the character to be checked
 *
 * Return: the result.
 */

char *p_build(char *val, char *tok)
{
	unsigned int le;
	char *ccm;

	le = _stringlength(val) + _stringlength(tok) + 2;
	ccm = malloc(sizeof(char) * le);

	if (ccm == NULL)
	{
		return (NULL);
	}
	memset(ccm, 0, le);

	ccm = _strconcat(ccm, val);
	ccm = _strconcat(ccm, "/");
	ccm = _strconcat(ccm, tok);
	return (ccm);
}

/**
 * _search_cmd - function to search in path
 * @c: the character to be checked
 * Return: the result.
 */

int _search_cmd(char **c)
{
	struct stat bf;
	char *ph, *vl, *c_ph;

	ph = _envget("PATH");
	vl = strtoken(ph, ":");

	while (vl != NULL)
	{
		c_ph = p_build(*c, vl);
		if (stat(c_ph, &bf) == 0)
		{
			*c = _duplicatestr(c_ph);
			free(c_ph);
			free(ph);
			return (0);
		}
		free(c_ph);
		vl = strtoken(NULL, ":");
	}
	free(ph);
	return (1);
}
