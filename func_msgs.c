#include "shell.h"

char *error127(char **args);
char *error126(char **args);
/**
 * error126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error126(char **args)
{
	char *error; 
	char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (NULL);
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
	_strcat(error, ": ");

	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_string);
	return (error);
}

/**
 * error127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error127(char **args)
{
	char *error;
        char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (NULL);
	}

	x = _strlen(name) + _strlen(hist_string) + _strlen(args[0]) + 16;

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
	_strcat(error, ": not found\n");

	free(hist_string);
	return (error);
}
