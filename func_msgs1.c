#include "shell.h"

char *error2_exit(char **args);
char *error2_cd(char **args);
char *error2_syntax(char **args);
char *errorenv(char **args);
char *error1(char **args);

/**
 * errorenv - func to Creates an error message for shellby_env errors.
 * @args: array of arguments passed to the command.
 *
 * Return: error string.
 */

char *errorenv(char **args)
{
	char *error;
	char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (NULL);
	}

	args--;
	x = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 45;

	error = malloc(sizeof(char) * (x + 1));
	if (!error)
	{
		free(hist_string);

		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");

	_strcat(error, hist_string);
	_strcat(error, ": ");

	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_string);
	return (error);
}

/**
 * error1 - func to creates an error message for shellby_alias errors.
 * @args: arguments passed to the command.
 *
 * Return: error string.
 */

char *error1(char **args)
{
	int i;
	char *err;

	i = _strlen(name) + _strlen(args[0]) + 13;

	err = malloc(sizeof(char) * (i + 1));

	if (!err)
	{
		return (NULL);
	}

	_strcpy(err, "alias: ");
	_strcat(err, args[0]);

	_strcat(err, " not found\n");

	return (err);
}

/**
 * error2_exit - func to Creates an error message for shellby_exit errors.
 * @args: array of arguments passed to the command.
 *
 * Return: the error string.
 */

char *error2_exit(char **args)
{
	char *error;
	char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (NULL);
	}

	x = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 27;

	error = malloc(sizeof(char) * (x + 1));
	if (!error)
	{
		free(hist_string);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");

	_strcat(error, hist_string);
	_strcat(error, ": exit: Illegal number: ");

	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_string);
	return (error);
}

/**
 * error2_cd - func to Creates an error message for shellby_cd errors.
 * @args: arguments passed to the command.
 *
 * Return: error string.
 */

char *error2_cd(char **args)
{
	char *error;
	char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (NULL);
	}

	if (args[0][0] == '-')
	{
		args[0][2] = '\0';
	}

	x = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 24;

	error = malloc(sizeof(char) * (x + 1));

	if (!error)
	{
		free(hist_string);

		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");

	_strcat(error, hist_string);

	if (args[0][0] == '-')
	{
		_strcat(error, ": cd: Illegal option ");
	}
	else
	{
		_strcat(error, ": cd: can't cd to ");
	}
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_string);
	return (error);
}

/**
 * error2_syntax - func to Creates an error message for syntax errors.
 * @args: array of arguments
 *
 * Return: The error string.
 */
char *error2_syntax(char **args)
{
	char *error;
	char *hist_string;
	int x;

	hist_string = _itoa(hist);
	if (!hist_string)
	{
		return (NULL);
	}

	x = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 33;

	error = malloc(sizeof(char) * (x + 1));
	if (!error)
	{
		free(hist_string);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");

	_strcat(error, hist_string);
	_strcat(error, ": Syntax error: \"");

	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_string);
	return (error);
}
