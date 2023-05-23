#include "shell.h"

void helpunsetenv(void);
void helphistory(void);
void helpenv(void);
void helpsetenv(void);

/**
 * helpenv - Displays information on the shellby builtin command 'env'.
 */

void helpenv(void)
{
	char *mssg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * helpunsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */

void helpunsetenv(void)
{
	char *mssg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "environmental variable.\n\n\tUpon failure, prints a ";

	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "message to stderr.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * helpsetenv - Displays information on the shellby builtin command 'setenv'.
 */

void helpsetenv(void)
{
	char *mssg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "environment variable, or modifies an existing one.\n\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "\tUpon failure, prints a message to stderr.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
}
