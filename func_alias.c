#include "shell.h"


void print_alias(alias_t *alias);
void set_alias(char *var_name, char *value);
int shell_alias(char **args, char __attribute__((__unused__)) **front);

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	char *new_value;
	int le, x;
	int i;

	*value = '\0';

	value++;

	le = _strlen(value) - _strspn(value, "'\"");

	new_value = malloc(sizeof(char) * (le + 1));

	if (!new_value)
	{
		return;
	}
	for (x = 0, i = 0; value[x]; x++)
	{
		if (value[x] != '\'' && value[x] != '"')
		{
			new_value[i++] = value[x];
		}
	}
	new_value[i] = '\0';

	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		addalias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_str;

	int l = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_str = malloc(sizeof(char) * (l + 1));

	if (!alias_str)
	{
		return;
	}
	_strcpy(alias_str, alias->name);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, l);

	free(alias_str);
}


/**
 * shell_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shell_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	char *val;
	int x, rx = 0;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (rx);
	}
	for (x = 0; args[x]; x++)
	{
		temp = aliases;

		val = _strchr(args[x], '=');

		if (!val)
		{
			while (temp)
			{
				if (_strcmp(args[x], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}

				temp = temp->next;
			}
			if (!temp)
			{
				rx = createerror(args + x, 1);
			}
		}
		else
		{
			set_alias(args[x], val);
		}
	}
	return (rx);
}


/**
 * replacealiases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replacealiases(char **args)
{
	alias_t *temp;
	char *new_val;
	int x;

	if (_strcmp(args[0], "alias") == 0)
	{
		return (args);
	}
	for (x = 0; args[x]; x++)
	{
		temp = aliases;

		while (temp)
		{
			if (_strcmp(args[x], temp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(temp->value) + 1));

				if (!new_val)
				{
					freeargs(args, args);
					return (NULL);
				}
				_strcpy(new_val, temp->value);
				free(args[x]);

				args[x] = new_val;
				x--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}

