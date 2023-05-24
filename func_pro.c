#include "shell.h"

int procfile_commands(char *filepath, int *exer);
int donot_open(char *filepath);

/**
 * donot_open - func to If the file doesn't exist or lacks proper permissions
 * @filepath: Path to the supposed file.
 *
 * Return: 0 always.
 */

int donot_open(char *filepath)
{
	char *error;
	char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (127);
	}

	x = _strlen(name) + _strlen(hist_string) + _strlen(filepath) + 16;

	error = malloc(sizeof(char) * (x + 1));

	if (!error)
	{
		free(hist_string);

		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");

	_strcat(error, hist_string);
	_strcat(error, ": Can't open ");

	_strcat(error, filepath);
	_strcat(error, "\n");

	free(hist_string);
	write(STDERR_FILENO, error, x);

	free(error);
	return (127);
}

/**
 * procfile_commands - func to Takes a file and attempts
 * @filepath: the Path to the file.
 * @exer: Return value of the last executed command.
 *
 * Return: the file couldn't be opened
 */
int procfile_commands(char *filepath, int *exer)
{
	ssize_t file, b_read;
	ssize_t	x;
	unsigned int linesize = 0;
	unsigned int oldsize = 120;
	char *line;
	char **args, **front;
	char buffer[120];
	int r;

	hist = 0;

	file = open(filepath, O_RDONLY);

	if (file == -1)
	{
		*exer = donot_open(filepath);
		return (*exer);
	}
	line = malloc(sizeof(char) * oldsize);

	if (!line)
	{
		return (-1);
	}
	do {
		b_read = read(file, buffer, 119);

		if (b_read == 0 && linesize == 0)
		{
			return (*exer);
		}

		buffer[b_read] = '\0';
		linesize += b_read;
		line = _realloc(line, oldsize, linesize);

		_strcat(line, buffer);
		oldsize = linesize;

	} while (b_read);

	for (x = 0; line[x] == '\n'; x++)
	{
		line[x] = ' ';
	}
	for (; x < linesize; x++)
	{
		if (line[x] == '\n')
		{
			line[x] = ';';

			for (x += 1; x < linesize && line[x] == '\n'; x++)
			{
				line[x] = ' ';
			}
		}
	}

	variablereplacement(&line, exer);
	handleline(&line, linesize);

	args = _strtok(line, " ");
	free(line);

	if (!args)
	{
		return (0);
	}

	if (checkargs(args) != 0)
	{
		*exer = 2;
		freeargs(args, args);

		return (*exer);
	}
	front = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;

			r = callargs(args, front, exer);
			args = &args[++x];
			x = 0;
		}
	}

	r = callargs(args, front, exer);

	free(front);
	return (r);
}
