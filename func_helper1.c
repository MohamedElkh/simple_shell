#include "shell.h"


char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);
void free_args(char **args, char **front);
char *get_pid(void);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	unsigned int x;

	for (x = 0; args[x] || args[x + 1]; x++)
	{
		free(args[x]);
	}

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	char *buffer;
	ssize_t f;
	unsigned int x = 0;

	f = open("/proc/self/stat", O_RDONLY);

	if (f == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(f);
		return (NULL);
	}
	read(f, buffer, 120);

	while (buffer[x] != ' ')
	{
		x++;
	}

	buffer[x] = '\0';

	close(f);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char *temp, *v;
	char **var_ad;
	char *replace = NULL; 

	v = malloc(len + 1);

	if (!v)
	{
		return (NULL);
	}
	v[0] = '\0';

	_strncat(v, beginning, len);

	var_ad = _getenv(v);

	free(v);
	if (var_ad)
	{
		temp = *var_ad;

		while (*temp != '=')
		{
			temp++;
		}

		temp++;

		replace = malloc(_strlen(temp) + 1);
		if (replace)
		{
			_strcpy(replace, temp);
		}
	}

	return (replace);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int j, x = 0, len;
	char *replace = NULL; 
	char *old = NULL, *new;

	old = *line;

	for (j = 0; old[j]; j++)
	{
		if (old[j] == '$' && old[j + 1] && old[j + 1] != ' ')
		{
			if (old[j + 1] == '$')
			{
				replace = get_pid();
				x = j + 2;
			}
			else if (old[j + 1] == '?')
			{
				replace = _itoa(*exe_ret);
				x = j + 2;
			}
			else if (old[j + 1])
			{
				/* extract the variable name to search for */
				for (x = j + 1; old[x] && old[x] != '$' && old[x] != ' '; x++)
				{
					;
				}

				len = x - (j + 1);
				replace = get_env_value(&old[j + 1], len);
			}
			new = malloc(j + _strlen(replace) + _strlen(&old[x]) + 1);

			if (!line)
			{
				return;
			}

			new[0] = '\0';
			_strncat(new, old, j);

			if (replace)
			{
				_strcat(new, replace);

				free(replace);
				replace = NULL;
			}
			_strcat(new, &old[x]);

			free(old);
			*line = new;

			old = new;
			j = -1;
		}
	}
}
