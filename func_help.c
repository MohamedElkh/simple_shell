#include "shell.h"

int _strcmp(char *s1, char *s2);
int _strspn(char *s, char *accept);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, char c);
/**
 * _strchr - Locates a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: If c is found - a pointer to the first occurence.
 *         If c is not found - NULL.
 */
char *_strchr(char *s, char c)
{
	int x;

	for (x = 0; s[x]; x++)
	{
		if (s[x] == c)
		{
			return (s + x);
		}
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int x;
	int byt = 0;

	while (*s)
	{
		for (x = 0; accept[x]; x++)
		{
			if (*s == accept[x])
			{
				byt++;
				break;
			}
		}

		s++;
	}
	return (byt);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;

		s2++;
	}

	if (*s1 != *s2)
	{
		return (*s1 - *s2);
	}

	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int x;

	for (x = 0; s1[x] && s2[x] && x < n; x++)
	{
		if (s1[x] > s2[x])
		{
			return (s1[x] - s2[x]);
		}
		else if (s1[x] < s2[x])
		{
			return (s1[x] - s2[x]);
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
