#include "shell.h"

char *getargs(char *line, int *exe_ret);
int callargs(char **args, char **front, int *exe_ret);

int runargs(char **args, char **front, int *exe_ret);
int handleargs(int *exe_ret);
int checkargs(char **args);


/**
 * getargs - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *getargs(char *line, int *exe_ret)
{
	size_t num = 0;
	ssize_t read;
	char *prompt = "$ ";


	if (line)
	{
		free(line);
	}

	read = _getline(&line, &num, STDIN_FILENO);

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
		return (getargs(line, exe_ret));
	}

	line[read - 1] = '\0';
	variablereplacement(&line, exe_ret);
	handleline(&line, read);

	return (line);
}

/**
 * callargs - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int callargs(char **args, char **front, int *exe_ret)
{
	int r;
	int i;

	if (!args[0])
	{
		return (*exe_ret);
	}
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);

			args[i] = NULL;
			args = replacealiases(args);
			r = runargs(args, front, exe_ret);

			if (*exe_ret != 0)
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

			r = runargs(args, front, exe_ret);
			if (*exe_ret == 0)
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

	r = runargs(args, front, exe_ret);
	return (r);
}

/**
 * runargs - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int runargs(char **args, char **front, int *exe_ret)
{
	int x, r;


	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		r = builtin(args + 1, front);
		if (r != EXIT)
		{
			*exe_ret = r;
		}
	}
	else
	{
		*exe_ret = execute(args, front);
		r = *exe_ret;
	}

	hist++;

	for (x = 0; args[x]; x++)
	{
		free(args[x]);
	}

	return (r);
}

/**
 * handleargs - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handleargs(int *exe_ret)
{
	char **args, *line = NULL;
	char **f;
	int x, ret = 0;

	line = getargs(line, exe_ret);
	if (!line)
	{
		return (END_OF_FILE);
	}

	args = _strtok(line, " ");
	free(line);
	if (!args)
	{
		return (ret);
	}
	if (checkargs(args) != 0)
	{
		*exe_ret = 2;

		freeargs(args, args);
		return (*exe_ret);
	}

	f = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;

			ret = callargs(args, f, exe_ret);
			args = &args[++x];
			x = 0;
		}
	}
	if (args)
	{
		ret = callargs(args, f, exe_ret);
	}

	free(f);
	return (ret);
}

/**
 * checkargs - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
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
