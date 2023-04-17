#include "shell.h"

/**
 * bul_echo - function to excute
 * @cm: the character to be checked
 * @str: the character to be checked
 *
 * Return: the result.
 */

int bul_echo(int str, char **cm)
{
	unsigned int p = getppid();
	char *pat;

	if (strncompare(cm[1], "$?", 2) == 0)
	{
		p_num(str);
		P_PRINT("\n");
	}
	else if (strncompare(cm[1], "$$", 2) == 0)
	{
		p_number(p);
		P_PRINT("\n");
	}
	else if (strncompare(cm[1], "$PATH", 5) == 0)
	{
		pat = _envget("PATH");
		P_PRINT(pat);
		P_PRINT("\n");
		free(pat);
	}
	else
	{
		return (echo_print(cm));
	}
	return (1);
}
