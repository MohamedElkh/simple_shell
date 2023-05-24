#include "shell.h"

char *_itoa(int number);
int num_len(int number);
int createerror(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @number: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int number)
{
	int l = 1;
	unsigned int n;

	if (number < 0)
	{
		l++;
		n = number * -1;
	}
	else
	{
		n = number;
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
 * @number: the integer.
 *
 * Return: The converted string.
 */
char *_itoa(int number)
{
	int l = num_len(number);
	char *buf;
	unsigned int n;

	buf = malloc(sizeof(char) * (l + 1));

	if (!buf)
	{
		return (NULL);
	}

	buf[l] = '\0';

	if (number < 0)
	{
		n = number * -1;

		buf[0] = '-';
	}
	else
	{
		n = number;
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
 * createerror - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @errs: the error value.
 *
 * Return: The error value.
 */

int createerror(char **args, int errs)
{
	char *er;

	switch (errs)
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
	return (errs);

}
