#include "shell.h"

/**
 * ch_del - function check char match any
 * @cc: the character to be checked
 * @s: the string to be checked
 *
 * Return: the result.
 */

size_t ch_del(char cc, const char *s)
{
	size_t x;

	for (x = 0; s[x] != '\0'; x++)
	{
		if (cc == s[x])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * strtoken - function a string to token
 * @s: the character to be checked
 * @del: the character to be checked
 *
 * Return: the result.
 */

char *strtoken(char *s, const char *deli)
{
	static char *cht;
        static char *chn;
	size_t x;

	if (s != NULL)
	{
		chn = s;
	}
	cht = chn;
	if (cht == NULL)
		return (NULL);
	for (x = 0; cht[x] != '\0'; x++)
	{
		if (ch_del(cht[x], deli) == 0)
		{
			break;
		}
	}
	if (chn[x] == '\0' || chn[x] == '#')
	{
		chn = NULL;
		return (NULL);
	}
	cht = chn + x;
	chn = cht;
	for (x = 0; chn[x] != '\0'; x++)
	{
		if (ch_del(chn[x], deli) == 1)
		{
			break;
		}
	}
	if (chn[x] == '\0')
	{
		chn = NULL;
	}
	else
	{
		chn[x] = '\0';
		chn = chn + x + 1;
		if (*chn == '\0')
		{
			chn = NULL;
		}
	}
	return (cht);
}
