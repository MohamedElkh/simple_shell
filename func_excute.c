#include "shell.h"

/**
 * f_signal_handel - function to handle the c
 * @n: the character to be checked
 *
 * Return: nothing.
 */

void f_signal_handel(int n)
{
	if (n == SIGINT)
	{
		P_PRINT("\n$ ");
	}
}

/**
 * func_cmd_check - the function to excute simple shell
 * @n: the character to be checked
 * @inp: the character to be checked
 * @cmd: the parsed command
 * @argv: the name of the program
 *
 * Return: the result.
 */

int func_cmd_check(int n, char *inp, char **cmd, char **argv)
{
	pid_t p;
	int stats;

	if (*cmd == NULL)
	{
		return (-1);
	}

	p = fork();

	if (p == -1)
	{
		perror("Error");
		return (-1);
	}

	if (p == 0)
	{
		if (strncompare(*cmd, "./", 2) != 0 && strncompare(*cmd, "/", 1) != 0)
		{
			_search_cmd(cmd);
		}
		if (execve(*cmd, cmd, environment) == -1)
		{
			display_error(n, cmd[0], argv);
			free(inp);
			free(cmd);
			exit(EXIT_FAILURE);
		}

		return (EXIT_FAILURE);
	}
	wait(&stats);
	return (0);
}

/**
 * f_handle_built - function to handle the built command
 * @last: the status of last excute
 * @cmd: the character to be checked
 *
 * Return: the result.
 */

int f_handle_built(int last, char **cmd)
{
	int x = 0;

	b_t p[] = {
		{"cd", dir_change},
		{"env", env_display},
		{"help", dis_env_help},
		{"echo", bul_echo},
		{"history", display_history},
		{NULL, NULL}
	};

	while ((p + x)->str)
	{
		if (_comparestr(cmd[0], (p + x)->str) == 0)
		{
			return ((p + x)->f(last, cmd));
		}
		x++;
	}
	return (-1);
}
