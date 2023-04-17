#include "shell.h"

/**
 * _stringlength - function to count the length of str
 * @str: the character to be checked
 *
 * Return: the result.
 */

int _stringlength(char *str)
{
	int x = 0;

	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}

/**
 * _putchar - write the character c to stdout
 * @c: the character to be checked
 *
 * Return: the result.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _pputs - function to print the string
 * @s: the character to be checked
 *
 * Return: nothing.
 */

void _pputs(char *s)
{
	int x;

	for (x = 0; s[x] != '\0'; x++)
	{
		_putchar(s[x]);
	}
	_putchar('\n');
}

/**
 * p_atoi - function to convert to intigar
 * @str: string
 *
 * Return: the result.
 */

int p_atoi(char *str)
{
	int a, nu, x, i;
	a = nu = 0;
	i = 1;

	while ((str[a] < '0' || str[a] > '9') && (str[a] != '\0'))
	{
		if (str[a] == '-')
		{
			i *= -1;
		}
		a++;
	}
	x = a;

	while ((str[x] >= '0') && (str[x] <= '9'))
	{
		nu = (nu * 10) + i * ((str[x]) - '0');
		x++;
	}
	return (nu);

}

/**
 * _strncopy - function to copy the string
 * @desti: the character to be checked
 * @src: the character to be checked
 * @num: the number to be checked
 *
 * Return: the result.
 */

char *_strncopy(char *desti, char *src, int num)
{
	int x = 0;

	while (x < num && *(src + x))
	{
		*(desti + x) = *(src + x);
		x++;
	}
	while (x < num)
	{
		*(desti + x) = '\0';
		x++;
	}
	return (desti);
}
