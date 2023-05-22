#include "shell.h"

int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);
int (*get_builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);

/**
 * get_builtin - Matches a command with a corresponding
 *               shellby builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t func[] = {
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ "exit", shell_exit},
		{ NULL, NULL }
	};

	int x;

	for (x = 0; func[x].name; x++)
	{
		if (_strcmp(func[x].name, command) == 0)
		{
			break;
		}
	}
	return (func[x].f);
}

/**
 * shell_exit - Causes normal process termination
 *                for the shellby shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int shell_exit(char **args, char **front)
{
	int x;
	int len_of = 10;
	unsigned int n = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			x = 1;
			len_of++;
		}
		for (; args[0][x]; x++)
		{
			if (x <= len_of && args[0][x] >= '0' && args[0][x] <= '9')
			{
				n = (n * 10) + (args[0][x] - '0');
			}
			else
			{
				return (createerror(--args, 2));
			}
		}
	}
	else
	{
		return (-3);
	}

	if (n > max - 1)
	{
		return (createerror(--args, 2));
	}
	args -= 1;
	freeargs(args, front);

	free_enve();

	freealias_list(aliases);
	exit(n);
}

/**
 * shell_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_in, *newline = "\n", *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);

	if (!oldpwd)
	{
		return (-1);
	}


	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') || args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
				{
					(chdir(*_getenv("OLDPWD") + 7));
				}
			}
			else
			{
				free(oldpwd);

				return (createerror(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) &&
					((dir.st_mode & S_IXUSR) != 0))
			{
				chdir(args[0]);
			}
			else
			{
				free(oldpwd);
				return (createerror(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
		{
			chdir(*(_getenv("HOME")) + 5);
		}
	}

	pwd = getcwd(pwd, 0);

	if (!pwd)
	{
		return (-1);
	}

	dir_in = malloc(sizeof(char *) * 2);

	if (!dir_in)
	{
		return (-1);
	}

	dir_in[0] = "OLDPWD";
	dir_in[1] = oldpwd;

	if (shell_setenv(dir_in, dir_in) == -1)
	{
		return (-1);
	}

	dir_in[0] = "PWD";
	dir_in[1] = pwd;

	if (shell_setenv(dir_in, dir_in) == -1)
	{
		return (-1);
	}
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));

		write(STDOUT_FILENO, newline, 1);
	}
	free(oldpwd);
	free(pwd);

	free(dir_in);
	return (0);
}

/**
 * shell_help - Displays information about shellby builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_help(char **args, char __attribute__((__unused__)) **front)
{


	if (!args[0])
	{
		helpall();
	}
	else if (_strcmp(args[0], "alias") == 0)
	{
		helpalias();
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		helpcd();
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		helpexit();
	}
	else if (_strcmp(args[0], "env") == 0)
	{
		helpenv();
	}
	else if (_strcmp(args[0], "setenv") == 0)
	{
		helpsetenv();
	}
	else if (_strcmp(args[0], "help") == 0)
	{
		helphelp();
	}
	else if (_strcmp(args[0], "unsetenv") == 0)
	{
		helpunsetenv();
	}
	else
	{
		write(STDERR_FILENO, name, _strlen(name));
	}

	return (0);
}
