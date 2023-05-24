#include "shell.h"

void p_alias(alias_t *alias);
void set_aliass(char *varnam, char *val);
int shell_alias(char **args, char __attribute__((__unused__)) **frov);

/**
 * set_aliass - function Will either set an existing alias 'name'
 * @varnam: the alias to be created or overwritten.
 * @val: this the Value of the alias. First character is a '='.
 */

void set_aliass(char *varnam, char *val)
{
	alias_t *tmp = aliases;
	char *new_value;
	int le, x;
	int i;

	*val = '\0';

	val++;

	le = _strlen(val) - _strspn(val, "'\"");

	new_value = malloc(sizeof(char) * (le + 1));

	if (!new_value)
	{
		return;
	}
	for (x = 0, i = 0; val[x]; x++)
	{
		if (val[x] != '\'' && val[x] != '"')
		{
			new_value[i++] = val[x];
		}
	}
	new_value[i] = '\0';

	while (tmp)
	{
		if (_strcmp(varnam, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		addalias_end(&aliases, varnam, new_value);
	}
}

/**
 * p_alias - func to Prints the alias in the format.
 * @alias: the Pointer to an alias.
 */

void p_alias(alias_t *alias)
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
 * @args: An array of arguments.
 * @frov: pointer to the beginning of args.
 *
 * Return: If an error occurs
 */

int shell_alias(char **args, char __attribute__((__unused__)) **frov)
{
	alias_t *tmp = aliases;
	char *val;
	int x, rx = 0;

	if (!args[0])
	{
		while (tmp)
		{
			p_alias(tmp);
			tmp = tmp->next;
		}
		return (rx);
	}
	for (x = 0; args[x]; x++)
	{
		tmp = aliases;

		val = _strchr(args[x], '=');

		if (!val)
		{
			while (tmp)
			{
				if (_strcmp(args[x], tmp->name) == 0)
				{
					p_alias(tmp);
					break;
				}

				tmp = tmp->next;
			}
			if (!tmp)
			{
				rx = createerror(args + x, 1);
			}
		}
		else
		{
			set_aliass(args[x], val);
		}
	}
	return (rx);
}


/**
 * replacealiases - the arguments and replace any matching alias
 * @args: pointer to the arguments.
 *
 * Return: pointer to the arguments.
 */

char **replacealiases(char **args)
{
	alias_t *tmp;
	char *new_val;
	int x;

	if (_strcmp(args[0], "alias") == 0)
	{
		return (args);
	}
	for (x = 0; args[x]; x++)
	{
		tmp = aliases;

		while (tmp)
		{
			if (_strcmp(args[x], tmp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(tmp->value) + 1));

				if (!new_val)
				{
					freeargs(args, args);

					return (NULL);
				}
				_strcpy(new_val, tmp->value);

				free(args[x]);

				args[x] = new_val;

				x--;
				break;
			}
			tmp = tmp->next;
		}
	}

	return (args);
}
