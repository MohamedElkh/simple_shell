#include "shell.h"

/**
 * echo_print - function to execute echo
 * @cm: the character to be checked
 * Return: the result.
 */

int echo_print(char **cm)
{
	pid_t p;
	int stat;

	p = fork();
	if (p == 0)
	{
		if (execve("/bin/echo", cm, environ) == -1)
		{
			return (-1);
		}
		exit(EXIT_FAILURE);
	}
	else if (p < 0)
	{
		return (-1);
	}
	else
	{
		do {
			waitpid(p, &stat, WUNTRACED);
		} while (!WIFEXITED(stat) && !WIFSIGNALED(stat));
	}
	return (1);
}

/**
 * display_history - function to display history
 * @cc: the character to be checked
 * @ss: the character to be checked
 *
 * Return: the result.
 */

int display_history(__attribute__((unused))char **cc, __attribute__((unused))int ss)
{
	char *flname = ".simple_shell_history";
	size_t le = 0;
	int count = 0;
	FILE *fl;
	char *err;
	char *lin = NULL;

	fl = fopen(flname, "r");
	if (fl == NULL)
	{
		return (-1);
	}

	while ((_takeline(&lin, &le, fl)) != -1)
	{
		count++;
		err = p_itoa(count);
		P_PRINT(err);
		free(err);
		P_PRINT(" ");
		P_PRINT(lin);
	}
	if (lin)
	{
		free(lin);
	}
	fclose(fl);
	return (0);}
