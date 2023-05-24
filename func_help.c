#include "shell.h"

int _strcmp(char *str1, char *str2);
int _strspn(char *str, char *acception);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strchr(char *str, char cha);
/**
 * _strchr - func to Locates a character a strings
 * @str: string to be searched.
 * @cha: character to be located.
 *
 * Return: if is found - a pointer
 */
char *_strchr(char *str, char cha)
{
	int x;

	for (x = 0; str[x]; x++)
	{
		if (str[x] == cha)
		{
			return (str + x);
		}
	}

	return (NULL);
}

/**
 * _strspn - func to Gets the length of a prefix substring.
 * @str: string to be searched.
 * @acception: The prefix
 *
 * Return: The number of bytes
 */
int _strspn(char *str, char *acception)
{
	int x;
	int byt = 0;

	while (*str)
	{
		for (x = 0; acception[x]; x++)
		{
			if (*str == acception[x])
			{
				byt++;
				break;
			}
		}

		str++;
	}
	return (byt);
}

/**
 * _strcmp - func to Compares two strings.
 * @str1: first string to be compared.
 * @str2: second string to be compared.
 *
 * Return: Positive byte difference
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;

		str2++;
	}

	if (*str1 != *str2)
	{
		return (*str1 - *str2);
	}

	return (0);
}

/**
 * _strncmp - func to Compare two strings.
 * @str1: pointer to a string.
 * @str2: pointer to a string.
 * @n: first n bytes of the strings to compare.
 *
 * Return: less than 0 if s1 is shorter than s2
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned int x;

	for (x = 0; str1[x] && str2[x] && x < n; x++)
	{
		if (str1[x] > str2[x])
		{
			return (str1[x] - str2[x]);
		}
		else if (str1[x] < str2[x])
		{
			return (str1[x] - str2[x]);
		}
	}
	if (x == n)
	{
		return (0);
	}
	else
	{
		return (-15);
	}
}
