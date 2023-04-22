#include "shell.h"

/**
 * c_arr_envi - function to create array of enivronment
 * @env: the array of environment
 *
 * Return: nothing.
 */

void c_arr_envi(char **env)
{
	int x;

	for (x = 0; environment[x]; x++)
	{
		env[x] = _duplicatestr(environment[x]);
	}
	env[x] = NULL;
}

/**
 * exit_shell - function to exit shell case of file
 * @li: line from the file
 * @cmd: the parsed command
 * @file: the character to be checked
 *
 * Return: nothing
 */

void exit_shell(char *li, char **cmd, FILE *file)
{
	int x = 0;
	int stats;

	if (cmd[1] == NULL)
	{
		free(li);
		free(cmd);
		fclose(file);
		exit(errno);
	}

	while (cmd[1][x])
	{
		if (_charaisa(cmd[1][x++]) < 0)
		{
			perror("illegal number");
		}
	}

	stats = p_atoi(cmd[1]);
	free(li);
	free(cmd);
	fclose(file);
	exit(stats);
}

/**
 * func_built_check - function to check builtin
 * @cm: the character to be checked
 *
 * Return: the result.
 */

int func_built_check(char **cm)
{
	b_t p[] = {
		{"cd", NULL},
		{"echo", NULL},
		{"help", NULL},
		{"history", NULL},
		{NULL, NULL}
	};

	int x = 0;
	if (*cm == NULL)
		return (-1);
	while ((p + x)->str)
	{
		if (_comparestr(cm[0], (p + x)->str) == 0)
		{
			return (0);
		}
		x++;
	}
	return (-1);
}

/**
 * check_t_file - function to parse check command
 * @count: the character to be checked
 * @li: the line from the file
 * @argv: the program name
 * @file: the file descriptor
 *
 * Return: nothing.
 */

void check_t_file(int count, char *li, char **argv, FILE *file)
{
	int str = 0;
	char **cmd;

	cmd = func_pasre(li);

	if (strncompare(cmd[0], "exit", 4) == 0)
	{
		exit_shell(li, cmd, file);
	}
	else if(func_built_check(cmd) == 0)
	{
		str = f_handle_built(str, cmd);
		free(cmd);
	}
	else
	{
		str = func_cmd_check(count, li, cmd, argv);
		free(cmd);
	}
}

/**
 * func_file_read - function to read the command from the file.
 * @name: the file name.
 * @argv: the program name
 *
 * Return: nothing.
 */

void func_file_read(char *name, char **argv)
{
	char *li = NULL;
	int count = 0;
	unsigned int length = 0;
	FILE *file;

	file = fopen(name, "r");

	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}

	while (-1 != (_takeline(&li, &length, file)))
	{
		count++;
		check_t_file(count, li, argv, file);
	}

	if (li)
	{
		free(li);
	}
	fclose(file);
	exit(0);
}

