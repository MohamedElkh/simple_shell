#include "shell.h"

/*
 * main - function of simple shell
 * @argc: the number of arguments
 * @argv: the name of program and the value
 *
 * Return: the result.
 */

int main(__attribute__((unused)) int argc, char **argv)
{
	int count = 0;
	int stats = 1;
	int val = 0;
	char **cmd;
	char *inp;

	if (argv[1] != NULL)
	{
		func_file_read(argv[1], argv);
	}
	signal(SIGINT, f_signal_handel);

	while (stats)
	{
		count++;
		if (isatty(STDIN_FILENO))
		{
			p_pro();
		}
		inp = _takeline();

		if (inp[0] == '\0')
			continue;
		fun_history(inp);
		cmd = func_pasre(inp);

		if (_comparestr(cmd[0], "exit") == 0)
		{
			built_exit(count, cmd, inp, argv);
		}
		else if (func_built_check(cmd) == 0)
		{
			val = f_handle_built(cmd, val);
			_arrfree(inp, cmd);
			continue;
		}
		else
		{
			val = func_cmd_check(count, inp, cmd, argv);
		}
		_arrfree(inp, cmd);
	}
	return (stats);
}
