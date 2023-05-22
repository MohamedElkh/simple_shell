#include "shell.h"

int proc_file_commands(char *file_path, int *exe_ret);
int cant_open(char *file_path);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error;
	char *hist_string;
	int x;

	hist_string = _itoa(hist);

	if (!hist_string)
	{
		return (127);
	}

	x = _strlen(name) + _strlen(hist_string) + _strlen(file_path) + 16;

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

	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_string);
	write(STDERR_FILENO, error, x);

	free(error);
	return (127);
}

/**
 * procfile_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int procfile_commands(char *file_path, int *exe_ret)
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

	file = open(file_path, O_RDONLY);

	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
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
			return (*exe_ret);
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

	variablereplacement(&line, exe_ret);
	handleline(&line, linesize);

	args = _strtok(line, " ");
	free(line);

	if (!args)
	{
		return (0);
	}

	if (checkargs(args) != 0)
	{
		*exe_ret = 2;
		freeargs(args, args);

		return (*exe_ret);
	}
	front = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;

			r = callargs(args, front, exe_ret);
			args = &args[++x];
			x = 0;
		}
	}

	r = callargs(args, front, exe_ret);

	free(front);
	return (r);
}
