#include "shell.h"


int execute(char **args, char **front);
void sig_handler(int sig);

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
	char *new_pro = "\n$ ";

	(void)sig;

	signal(SIGINT, sig_handler);

	write(STDIN_FILENO, new_pro, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{

int status;
int fg = 0, r = 0;
pid_t child_pid;
char *command = args[0];

if (command[0] != '/' && command[0] != '.')
{
	fg = 1;

	command = getlocation(command);
}

if (!command || (access(command, F_OK) == -1))
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
	child_pid = fork();

	if (child_pid == -1)
	{
		if (fg)
		{
			free(command);
		}

		perror("Error child:");
		return (1);
	}
	if (child_pid == 0)
	{
		execve(command, args, environ);

		if (errno == EACCES)
		{
			r = (createerror(args, 126));
		}

		free_enve();
		freeargs(args, front);
		freealias_list(aliases);
		_exit(r);
	}
	else
	{
		wait(&status);
		r = WEXITSTATUS(status);
	}
}
if (fg)
{
	free(command);
}
return (r);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int r = 0, ret;
	int *exe_ret = &ret;
	char *prompt = "$ ", *newline = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenve();
	if (!environ)
	{
		exit(-100);
	}

	if (argc != 1)
	{
		r = procfile_commands(argv[1], exe_ret);

		free_enve();
		freealias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (r != END_OF_FILE && r != EXIT)
		{
			r = handleargs(exe_ret);
		}
		free_enve();
		freealias_list(aliases);

		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);

		r = handleargs(exe_ret);
		if (r == END_OF_FILE || r == EXIT)
		{
			if (r == END_OF_FILE)
			{
				write(STDOUT_FILENO, newline, 1);
			}

			free_enve();
			freealias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_enve();
	freealias_list(aliases);
	return (*exe_ret);
}
