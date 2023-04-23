 "shell.h"

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

/**
 * env_display - function to display environment
 * @last: status of last command excuted
 * @cmm: parsed command
 *
 * Return: the result.
 */

int env_display(__attribute__((unused)) int last, __attribute__((unused)) char **cmm)
{
	int length;
	unsigned int x;

	for (x = 0; environment[x] != NULL; x++)
	{
		length = _stringlength(environment[x]);
		write(1, environment[x], length);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * dis_env_help - function to display help
 * @last: status of last command
 * @cmm: parsed command
 *
 * Return: the result.
 */

int dis_env_help(__attribute__((unused)) int last, char **cmm)
{
	char s;
	int rdf = 1, fwf, fdf;

	fdf = open(cmm[1], O_RDONLY);

	if (fdf < 0)
	{
		perror("Error");
		return (0);
	}

	while (rdf > 0)
	{
		rdf = read(fdf, &s, 1);
		fwf = write(STDOUT_FILENO, &s, rdf);

		if (fwf < 0)
			return (-1);
	}
	_putchar('\n');
	return (0);
}

/**
 * dir_change - function to change the directory
 * @last: the status of last command
 * @cmd: the parsed command
 *
 * Return: the result.
 */

int dir_change(__attribute__((unused)) int last, char **cmd)
{
	char cwd[PATH_MAX];
	int val = -1;

	if (cmd[1] == NULL)
	{
		val = chdir(getenv("HOME"));
	}
	else if (_comparestr(cmd[1], "-") == 0)
	{
		val = chdir(getenv("OLDPWD"));
	}
	else
	{
		val = chdir(cmd[1]);
	}

	if (val == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (val != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}

/**
 * built_exit - function to exit the statue shell
 * @s: the excute count
 * @cmd: the parsed command
 * @input: the user input
 * @argv: the name of the program
 *
 * Return: nothing.
 */

void built_exit(int s, char **cmd, char *input, char **argv)
{
	int x = 0;
	int stats;

	if (cmd[1] == NULL)
	{
		free(input);
		free(cmd);
		exit(EXIT_SUCCESS);
	}

	while (cmd[1][x])
	{
		if (_charaisa(cmd[1][x++]) != 0)
		{
			prin_error(s, cmd, argv);
			break;
		}
		else
		{
			stats = p_atoi(cmd[1]);
			free(input);
			free(cmd);
			exit(stats);
		}
	}

}
