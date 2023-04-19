#include "shell.h"

/**
 * enviro_free - a function to free the environment of variable array
 * @en: the pointer to be checked
 *
 * Return: nothing .
 */

void enviro_free(char **en)
{
	int x;

	for (x = 0; en[x]; x++)
	{
		free(en[x]);
	}
}

/**
 * fun_history - function to fill file by the user
 * @inp: the character to be checked
 *
 * Return: the result .
 */

int fun_history(char *inp)
{
	ssize_t fdf, wf;
	int le = 0;
	char *namefile = ".simple_shell_history";

	if (!namefile)
	{
		return (-1);
	}

	fdf = open(namefile, O_CREAT | O_RDWR | O_APPEND, 00600);

	if (fdf < 0)
	{
		return (-1);
	}

	if (inp)
	{
		while (inp[le])
		{
			le++;
		}
		wf = write(fdf, inp, le);

		if (we < 0)
		{
			return (-1);
		}
	}
	return (1);
}
