#include "shell.h"


int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
	int l = 0;

	if (!s)
	{
		return (l);
	}
	for (l = 0; s[l]; l++)
	{
		;
	}
	return (l);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	unsigned int x;

	for (x = 0; src[x] != '\0'; x++)
	{
		dest[x] = src[x];
	}
	dest[x] = '\0';

	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
	const char *temp;
	char *newdest;

	temp =  src;
	newdest = dest;

	while (*newdest != '\0')
	{
		newdest++;
	}

	while (*temp != '\0')
	{
		*newdest++ = *temp++;
	}
	*newdest = '\0';

	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t len = _strlen(dest);
	unsigned int x;

	for (x = 0; x < n && src[x] != '\0'; x++)
	{
		dest[len + x] = src[x];
	}
	dest[len + x] = '\0';

	return (dest);
}
