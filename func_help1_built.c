#include "shell.h"

void helpcd(void);
void helpexit(void);
void helphelp(void);
void helpall(void);
void helpalias(void);

/**
 * helpall - the Displays all possible builtin shell
 */

void helpall(void)
{
	char *mssg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * helpalias - the Displays information on the shellby builtin command
 */

void helpalias(void)
{
	char *mssg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * helpcd - the Displays information on the shellby builtin command
 */

void helpcd(void)
{
	char *mssg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "after a change of directory.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * helpexit - the Displays information on the shellby builtin command
 */

void helpexit(void)
{
	char *mssg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, mssg, _strlen(mssg));

	mssg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = " exit 0.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * helphelp - the Displays information on the shellby builtin command
 */

void helphelp(void)
{
	char *mssg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "builtin command.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}
