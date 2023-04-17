#include "shell.h"

/**
 * _copymem - function to copy byte from src
 * @src: the source
 * @desti: the character to be checked
 * @num: the number to be checked
 *
 * Return: the result.
 */

char *_copymem(char *src, char *desti, size_t num)
{
	size_t x;

	for (x = 0; x < num; x++)
	{
		desti[x] = src[x];
	}
	return (desti);
}

/**
 * _arrfree - function to free array of char
 * @ch: the character to be checked
 * @cm: the array
 *
 * Return: nothing.
 */

void _arrfree(char *ch, char **cm)
{
	free(cm);
	free(ch);
	cm = NULL;
	ch = NULL;
}

/**
 * _locatemem - function to allocates memory
 * @value: the size.
 *
 * Return: nothing.
 */

void *_locatemem(unsigned int value)
{
	unsigned int x;
	char *val;

	if (value == 0)
	{
		return (NULL);
	}
	val = malloc(value);
	if (val == NULL)
	{
		return (NULL);
	}
	for (x = 0; x < value; x++)
	{
		val[x] = '\0';
	}
	return (val);
}

/**
 * arr_filled - function to fill the array by byte
 * @n: the character to be checked
 * @le: the length
 * @p: void pointer
 *
 * Return: nothing.
 */

void *arr_filled(int n, unsigned int le, void *p)
{
	unsigned int x = 0;
	char *ptr = p;

	while (x < le)
	{
		*ptr = n;
		ptr++;
		x++;
	}
	return (p);
}

/**
 * fre_locate - function tp relocate the memory
 * @p: pointer to be checked
 * @oldvalue: the previous size of the pointer
 * @newvale: the new value of the pointer
 *
 * Return: nothing.
 */

void *fre_locate(void *p, size_t oldvalue, size_t newvalue)
{
	void *res;

	if (newvalue == oldvalue)
	{
		return (p);
	}
	if (newvalue == 0 && p)
	{
		free(p);
		return (NULL);
	}
	res = malloc(newvalue);
	if (res == NULL)
		return (NULL);
	if (p == NULL)
	{
		arr_filled(res, '\0', newvalue);
		free(p);
	}
	else
	{
		_copymem(res, '\0', newvalue);
		free(p);
	}
	return (res);
}


