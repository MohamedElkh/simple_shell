#include "shell.h"


char *getenv_value(char *beginning, int len);
void variablereplacement(char **line, int *exret);
void freeargs(char **args, char **main);
char *gett_pid(void);

/**
 * freeargs - func to Frees up memory taken by args.
 * @args: null-terminated double pointer containing commands/arguments.
 * @main: double pointer to the beginning of args.
 *
 * Return: nothing.
 */

void freeargs(char **args, char **main)
{
	unsigned int x;

	for (x = 0; args[x] || args[x + 1]; x++)
	{
		free(args[x]);
	}

	free(main);
}

/**
 * gett_pid - Gets the current process ID.
 * @void: nothing.
 * Description: the Opens the stat file, a space-delimited file containing
 *
 * Return: current process ID or NULL on failure.
 */

char *gett_pid(void)
{
	char *buff;
	ssize_t f;
	unsigned int x = 0;

	f = open("/proc/self/stat", O_RDONLY);

	if (f == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buff = malloc(120);

	if (!buff)
	{
		close(f);
		return (NULL);
	}
	read(f, buff, 120);

	while (buff[x] != ' ')
	{
		x++;
	}

	buff[x] = '\0';

	close(f);
	return (buff);
}

/**
 * getenv_value - func to Gets the value corresponding to an enviro var
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Description: Variables are stored in the format .
 * Return: variable is not found
 */

char *getenv_value(char *beginning, int len)
{
	char *tmp, *v;
	char **var_v;
	char *replce = NULL;

	v = malloc(len + 1);

	if (!v)
	{
		return (NULL);
	}
	v[0] = '\0';

	_strncat(v, beginning, len);

	var_v = _getenv(v);

	free(v);
	if (var_v)
	{
		tmp = *var_v;

		while (*tmp != '=')
		{
			tmp++;
		}

		tmp++;

		replce = malloc(_strlen(tmp) + 1);

		if (replce)
		{
			_strcpy(replce, tmp);
		}
	}

	return (replce);
}

/**
 * variablereplacement - func to Handles variable replacement.
 * @line: the double pointer containing the command and arguments.
 * @exret: the pointer to the return value of the last executed command.
 *
 * Description: the Replaces $$ with the current PID, $?
 * Return: nothing.
 */

void variablereplacement(char **line, int *exret)
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
				replace = gett_pid();

				x = j + 2;
			}
			else if (old[j + 1] == '?')
			{
				replace = _itoa(*exret);

				x = j + 2;
			}
			else if (old[j + 1])
			{

				for (x = j + 1; old[x] && old[x] != '$' && old[x] != ' '; x++)
				{
					;
				}

				len = x - (j + 1);
				replace = getenv_value(&old[j + 1], len);
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
