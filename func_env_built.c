#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);


/**
 * shell_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shell_env(char **args, char __attribute__((__unused__)) **front)
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
 * shell_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **front)
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
 * shell_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front)
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
