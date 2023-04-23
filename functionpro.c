 "shell.h"

/**
 * p_pro - function to display shell prompt
 * @void: nothing.
 *
 * Return: nothing.
 */

void p_pro(void)
{
	P_PRINT("$ ");
}

/**
 * display_error - function to display error
 * @count: the character to be checked
 * @inp: the user input
 * @argv: the name of the program
 *
 * Return: nothing.
 */

void display_error(int count, char *inp, char **argv)
{
	char *val;

	P_PRINT(argv[0]);
	P_PRINT(": ");
	val = p_itoa(count);
	P_PRINT(val);
	free(val);
	P_PRINT(": ");
	P_PRINT(inp);
	P_PRINT(": not found\n");
}

/**
 * prin_error - function to print error
 * @n: count of errors
 * @cm: the character to be checked
 * @argv: the program name
 *
 * Return: nothing.
 */

void prin_error(int n, char **cm, char **argv)
{
	char *val = p_itoa(n);

	P_PRINT(argv[0]);
	P_PRINT(": ");
	P_PRINT(val);
	P_PRINT(": ");
	P_PRINT(cm[0]);
	P_PRINT(": legal number: ");
	P_PRINT(cm[1]);
	P_PRINT("\n");
	P_PRINT(val);
}
