#include "shell.h"

char *_itoa(int num);
int num_len(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	int l = 1;
	unsigned int n;

	if (num < 0)
	{
		l++;
		n = num * -1;
	}
	else
	{
		n = num;
	}
	while (n > 9)
	{
		l++;
		n /= 10;
	}

	return (l);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	int l = num_len(num);
	char *buf;
	unsigned int n;

	buf = malloc(sizeof(char) * (l + 1));
	if (!buf)
	{
		return (NULL);
	}

	buf[l] = '\0';

	if (num < 0)
	{
		n = num * -1;
		buf[0] = '-';
	}
	else
	{
		n = num;
	}

	l--;

	do {
		buf[l] = (n % 10) + '0';
		n /= 10;
		l--;
	} while (n > 0);

	return (buf);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *er;

	switch (err)
	{
	case -1:
		er = errorenv(args);
		break;
	case 1:
		er = error1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
		{
			er = error2_exit(++args);
		}
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
		{
			er = error2_syntax(args);
		}
		else
		{
			er = error2_cd(args);
		}
		break;
	case 126:
		er = error126(args);
		break;
	case 127:
		er = error127(args);
		break;
	}
	write(STDERR_FILENO, er, _strlen(er));

	if (er)
	{
		free(er);
	}
	return (err);

}
