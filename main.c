#include "shell.h"


int execute(char **args, char **main);
void do_handler(int x);

/**
 * execute - func to Executes a command in a child process.
 * @args: array of arguments.
 * @main: A double pointer to the beginning of args.
 *
 * Return: if an error occurs - a corresponding error code.
 */

int execute(char **args, char **main)
{

	int sts;
	int fg = 0, r = 0;

	pid_t ch_pid;

	char *order = args[0];

	if (order[0] != '/' && order[0] != '.')
	{
		fg = 1;

		order = getlocation(order);
	}

	if (!order || (access(order, F_OK) == -1))
	{
		if (errno == EACCES)
		{
			r = (createerror(args, 126));
		}
		else
		{
			r = (createerror(args, 127));
		}
	}
	else
	{
		ch_pid = fork();

		if (ch_pid == -1)
		{
			if (fg)
			{
				free(order);
			}

			perror("Error child:");
			return (1);
		}
		if (ch_pid == 0)
		{
			execve(order, args, environ);

			if (errno == EACCES)
			{
				r = (createerror(args, 126));
			}

			free_enve();
			freeargs(args, main);

			freealias_list(aliases);
			_exit(r);
		}
		else
		{
			wait(&sts);
			r = WEXITSTATUS(sts);
		}
	}
	if (fg)
	{
		free(order);
	}
	return (r);
}

/**
 * do_handler - func to Prints a new prompt upon a signal.
 * @x: signal.
 */

void do_handler(int x)
{
	char *new_pro = "\n$ ";

	(void)x;

	signal(SIGINT, do_handler);

	write(STDIN_FILENO, new_pro, 3);
}

/**
 * main - func to runs a simple UNIX command interpreter.
 * @argc: nums of arguments supplied to the program.
 * @argv: pointers to the arguments.
 *
 * Return: 0 Always.
 */

int main(int argc, char *argv[])
{
	int r = 0, ret;
	int *exret = &ret;
	char *prompt = "$ ", *newline = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, do_handler);

	*exret = 0;
	environ = _copyenve();
	if (!environ)
	{
		exit(-100);
	}

	if (argc != 1)
	{
		r = procfile_commands(argv[1], exret);

		free_enve();

		freealias_list(aliases);
		return (*exret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (r != END_OF_FILE && r != EXIT)
		{
			r = handleargs(exret);
		}
		free_enve();

		freealias_list(aliases);

		return (*exret);
	}

	while (1)
	{

		write(STDOUT_FILENO, prompt, 2);

		r = handleargs(exret);

		if (r == END_OF_FILE || r == EXIT)
		{
			if (r == END_OF_FILE)
			{
				write(STDOUT_FILENO, newline, 1);
			}

			free_enve();
			freealias_list(aliases);

			exit(*exret);
		}
	}

	free_enve();
	freealias_list(aliases);
	return (*exret);
}
