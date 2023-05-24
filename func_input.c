#include "shell.h"

char *getargs(char *lin, int *exret);
int callargs(char **args, char **main, int *exret);

int runargs(char **args, char **main, int *exret);
int handleargs(int *exret);
int checkargs(char **args);


/**
 * getargs - func to Gets a command from standard input.
 * @lin: buffer to store the command.
 * @exret: return value of the last executed command.
 *
 * Return: if an error occurs
 */

char *getargs(char *lin, int *exret)
{
	size_t num = 0;
	ssize_t read;
	char *prompt = "$ ";


	if (lin)
	{
		free(lin);
	}

	read = _getline(&lin, &num, STDIN_FILENO);

	if (read == -1)
	{
		return (NULL);
	}
	if (read == 1)
	{
		hist++;

		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, prompt, 2);
		}
		return (getargs(lin, exret));
	}

	lin[read - 1] = '\0';

	variablereplacement(&lin, exret);
	handleline(&lin, read);

	return (lin);
}

/**
 * callargs -func to Partitions operators from commands and calls them.
 * @args: array of arguments.
 * @main: double pointer to the beginning of args.
 * @exret: return val of the parent process' last executed command.
 *
 * Return: the last executed command.
 */

int callargs(char **args, char **main, int *exret)
{
	int r;
	int i;

	if (!args[0])
	{
		return (*exret);
	}
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);

			args[i] = NULL;
			args = replacealiases(args);
			r = runargs(args, main, exret);

			if (*exret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
				{
					free(args[i]);
				}
				return (r);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);

			args[i] = NULL;
			args = replacealiases(args);

			r = runargs(args, main, exret);

			if (*exret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
				{
					free(args[i]);
				}
				return (r);
			}
		}
	}
	args = replacealiases(args);

	r = runargs(args, main, exret);
	return (r);
}

/**
 * runargs - func to Calls the execution of a command.
 * @args: array of arguments.
 * @main: double pointer to the beginning of args.
 * @exret: value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */

int runargs(char **args, char **main, int *exret)
{
	int x, r;


	int (*builtin)(char **args, char **main);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		r = builtin(args + 1, main);
		if (r != EXIT)
		{
			*exret = r;
		}
	}
	else
	{
		*exret = execute(args, main);
		r = *exret;
	}

	hist++;

	for (x = 0; args[x]; x++)
	{
		free(args[x]);
	}

	return (r);
}

/**
 * handleargs - func to Gets, calls, and runs the execution of a command.
 * @exret: return value of the parent process' last executed command.
 *
 * Return: an end-of-file is read - END_OF_FILE
 */

int handleargs(int *exret)
{
	char **args, *li = NULL;
	char **f;
	int x, ret = 0;

	li = getargs(li, exret);
	if (!li)
	{
		return (END_OF_FILE);
	}

	args = _strtok(li, " ");
	free(li);

	if (!args)
	{
		return (ret);
	}
	if (checkargs(args) != 0)
	{
		*exret = 2;

		freeargs(args, args);
		return (*exret);
	}

	f = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;

			ret = callargs(args, f, exret);

			args = &args[++x];
			x = 0;
		}
	}
	if (args)
	{
		ret = callargs(args, f, exret);
	}

	free(f);
	return (ret);
}

/**
 * checkargs - func to Checks if there are any leading
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: 0 always
 */
int checkargs(char **args)
{
	unsigned int x;
	char *cur, *nx;

	for (x = 0; args[x]; x++)
	{
		cur = args[x];

		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (x == 0 || cur[1] == ';')
			{
				return (createerror(&args[x], 2));
			}

			nx = args[x + 1];
			if (nx && (nx[0] == ';' || nx[0] == '&' || nx[0] == '|'))
			{
				return (createerror(&args[x + 1], 2));
			}
		}
	}
	return (0);
}
