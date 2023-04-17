#include "shell.h"

/**
 * rev_arr - function to reverse array
 * @array: the array to be reversed
 * @le: the length of the array
 *
 * Return: nothing.
 */

void rev_arr(char *array, int le)
{
	char val;
	int x;

	for (x = 0; x < (le / 2); x++)
	{
		val = array[x];
		array[x] = array[(le - 1) - x];
		array[(le - 1) - x] = val;
	}
}

/**
 * _lengthint - function to determine the len of int
 * @n: the character to be checked
 *
 * Return: the result.
 */

int _lengthint(int n)
{
	int le = 0;

	while (n != 0)
	{
		le++;
		n /= 10;
	}
	return (le);
}

/**
 * _charaisa - function to check
 * @n: the character to be checked
 *
 * Return: the result.
 */

int _charaisa(int n)
{
	if (((n >= 97) && (n <= 122)) || ((n >= 65) && (n <= 90)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _comparestr - function to compare two str
 * @str: the first character to be checked
 * @str2: the second character to be checked
 *
 * Return: the result.
 */

int _comparestr(char *str, char *str2)
{
	int x, val = 0;
	int le, le2;

	le = _stringlength(str);
	le2 = _stringlength(str2);

	if (str == NULL || str2 == NULL)
	{
		return (1);
	}
	if (le != le2)
	{
		return (1);
	}
	for (x = 0; str[x] != '\0'; x++)
	{
		if (str[x] != str2[x])
		{
			val = str[x] - str2[x];
			break;
		}
		else
		{
			continue;
		}
	}
	return (val);
}

/**
 * p_itoa - function to convert int to char
 * @num: the character to be checked
 *
 * Return: the result.
 */

char *p_itoa(size_t num)
{
	char *str;
	int le = 0, x = 0;

	le = _lengthint(num);
	str = malloc(le + 1);

	if (!str)
		return (NULL);
	*str = '\0';
	while (num / 10)
	{
		str[x] = (num % 10) + '0';
		num /= 10;
		x++;
	}
	str[x] = (num % 10) + '0';
	rev_arr(str, le);
	str[x + 1] = '\0';
	return (str);

}


