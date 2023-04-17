#include "shell.h"

/**
 * strchara - function locate char in str
 * @str: character to be checked
 * @cc: the character to be checked
 *
 * Return: the result.
 */

char *strchara(char *str, char cc)
{
	do
	{
		if (*str == cc)
		{
			break;
		}

	} while (*str++);
	return (str);
}

/**
 * strcopy - function to copy the source
 * @desti: the character to be checked
 * @src: the character to be checked
 *
 * Return: the result.
 */

char *strcopy(char *desti, char *src)
{
	int x = 0;

	while (src[x] != '\0')
	{
		desti[x] = src[x];
		x++;
	}
	desti[x] = '\0';
	return (desti);
}

/**
 * strncompare - function to compare between num of two str
 * @str: character to be checked
 * @str2: the character to be checked
 * @num: the number to be checked
 *
 * Return: the result.
 */

int strncompare(const char *str, const char *str2, unsigned int num)
{
	unsigned int x;

	if (str == NULL)
	{
		return (-1);
	}

	for (x = 0; x < num && str2[x]; x++)
	{
		if (str[x] != str2[x])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _strconcat - function to concat two str
 * @desti: the character to be checked
 * @src: the character to be checked
 *
 * Return: the result.
 */

char *_strconcat(char *desti, char *src)
{
	char *str = desti;

	while (*desti != '\0')
	{
		desti++;
	}
	while (*src != '\0')
	{
		*desti = *src;
		desti++;
		src++;
	}
	*desti = '\0';
	return (str);
}

/**
 * _duplicatestr - function to duplicate str
 * @s: the character to be checked
 *
 * Return: the result.
 */

char *_duplicatestr(char *s)
{
	char *s2;
	unsigned int le, x;

	le = _stringlength(s);
	s2 = malloc(sizeof(char) * (le + 1));

	if (!s2)
	{
		return (NULL);
	}
	for (x = 0; x <= le; x++)
	{
		s2[x] = s[x];
	}
	return (s2);
}

