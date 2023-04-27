#include "shell.h"

/**
 * _strchr - function locate char in str
 * @str: character to be checked
 * @cc: the character to be checked
 *
 * Return: the result.
 */

char *_strchr(char *str, char cc)
{
	do {
	
		if (*str == cc)
		{
			break;
		}

	} while (*str++);
	return (str);
}

/**
 * _strcpy - function to copy the source
 * @desti: the character to be checked
 * @sr: the character to be checked
 *
 * Return: the result.
 */

char *_strcpy(char *desti, char *sr)
{
	int x = 0;

	while (src[x] != '\0')
	{
		desti[x] = sr[x];
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
 * Return: thie result.
 */

int _strncmp(const char *str, const char *str2, unsigned int num)
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
 * _strcat - function to concat two str
 * @desti: the character to be checked
 * @sr: the character to be checked
 *
 * Return: the result.
 */

char *_strcat(char *desti, char *sr)
{
	char *str = desti;

	while (*desti != '\0')
	{
		desti++;
	}
	while (*sr != '\0')
	{
		*desti = *src;
		desti++;
		sr++;
	}
	*desti = '\0';
	return (str);
}

/**
 * _strdup - function to duplicate str
 * @s: the character to be checked
 *
 * Return: the result.
 */

char *_strdup(char *s)
{
	char *s2;
	unsigned int le, x;

	le = _strlen(s);
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

