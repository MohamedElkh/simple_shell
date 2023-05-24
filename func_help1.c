#include "shell.h"


int _strlen(const char *str);
char *_strcat(char *desti, const char *srcs);
char *_strcpy(char *desti, const char *srcs);
char *_strncat(char *desti, const char *srcs, size_t n);

/**
 * _strlen - function toReturns the length of a string.
 * @str: pointer to the characters string.
 *
 * Return: The length of the character string.
 */

int _strlen(const char *str)
{
	int l = 0;

	if (!str)
	{
		return (l);
	}
	for (l = 0; str[l]; l++)
	{
		;
	}
	return (l);
}

/**
 * _strcpy - func to copies the string pointed to by src, including the
 * @desti: the Pointer to the destination of copied string.
 * @srcs: the src of the source string.
 *
 * Return: Pointer to dest.
 */

char *_strcpy(char *desti, const char *srcs)
{
	unsigned int x;

	for (x = 0; srcs[x] != '\0'; x++)
	{
		desti[x] = srcs[x];
	}
	desti[x] = '\0';

	return (desti);
}

/**
 * _strcat - func to Concantenates two strings.
 * @desti: the Pointer to destination string.
 * @srcs: the Pointer to source string.
 *
 * Return: the Pointer to destination string.
 */

char *_strcat(char *desti, const char *srcs)
{
	const char *tmp;
	char *newdest;

	tmp =  srcs;
	newdest = desti;

	while (*newdest != '\0')
	{
		newdest++;
	}

	while (*tmp != '\0')
	{
		*newdest++ = *tmp++;
	}
	*newdest = '\0';

	return (desti);
}

/**
 * _strncat - func to Concantenates two strings where n number
 * @desti: the Pointer to destination string.
 * @srcs: the Pointer to source string.
 * @n: num of  bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */

char *_strncat(char *desti, const char *srcs, size_t n)
{
	size_t len = _strlen(desti);
	unsigned int x;

	for (x = 0; x < n && srcs[x] != '\0'; x++)
	{
		desti[len + x] = srcs[x];
	}
	desti[len + x] = '\0';

	return (desti);
}
