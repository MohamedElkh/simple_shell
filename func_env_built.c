#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **frov);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **frov);
int shell_setenv(char **args, char __attribute__((__unused__)) **frov);


/**
 * shell_env - func to Prints the current environment.
 * @args: array of arguments
 * @frov: the double pointer to the beginning of args.
 *
 * Description: Prints one variable per line
 * Return: 0 always.
 */

int shell_env(char **args, char __attribute__((__unused__)) **frov)
{
	int i;
	char newline = '\n';

	if (!environ)
	{
		return (-1);
	}

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &newline, 1);
	}

	(void)args;

	return (0);
}

/**
 * shell_setenv - func to Changes or adds an environmental
 * @args: An array of arguments
 * @frov: pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *
 * Return: If an error occurs - -1 or  0.
 */

int shell_setenv(char **args, char __attribute__((__unused__)) **frov)
{
	char **env_var = NULL, **new_enviro;
	char *new_val;
	size_t size;
	int i;

	if (!args[0] || !args[1])
	{
		return (createerror(args, -1));
	}

	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);

	if (!new_val)
	{
		return (createerror(args, -1));
	}

	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");

	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);

	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;

		return (0);
	}
	for (size = 0; environ[size]; size++)
	{
		;
	}

	new_enviro = malloc(sizeof(char *) * (size + 2));

	if (!new_enviro)
	{
		free(new_val);
		return (createerror(args, -1));
	}

	for (i = 0; environ[i]; i++)
	{
		new_enviro[i] = environ[i];
	}

	free(environ);
	environ = new_enviro;

	environ[i] = new_val;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - func to Deletes an environmental variable from the PATH.
 * @args: An array of arguments
 * @frov: pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs 0 always.
 */

int shell_unsetenv(char **args, char __attribute__((__unused__)) **frov)
{
	char **new_enviro, **env_var;
	int i, x;
	size_t size;

	if (!args[0])
	{
		return (createerror(args, -1));
	}

	env_var = _getenv(args[0]);
	if (!env_var)
	{
		return (0);
	}

	for (size = 0; environ[size]; size++)
	{
		;
	}

	new_enviro = malloc(sizeof(char *) * size);

	if (!new_enviro)
	{
		return (createerror(args, -1));
	}

	for (i = 0, x = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			continue;
		}
		new_enviro[x] = environ[i];
		x++;
	}
	free(environ);
	environ = new_enviro;
	environ[size - 1] = NULL;

	return (0);
}

