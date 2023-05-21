#include "shell.h"

list_t *get_path_dir(char *path);
char *fill_path_dir(char *path);

/**
 * get_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *get_location(char *command)
{
	list_t *dire, *head;
	struct stat str;
	char **p, *temp;

	p = _getenv("PATH");

	if (!p || !(*p))
	{
		return (NULL);
	}

	dire = get_path_dir(*p + 5);

	head = dire;

	while (dire)
	{
		temp = malloc(_strlen(dire->dir) + _strlen(command) + 2);

		if (!temp)
		{
			return (NULL);
		}

		_strcpy(temp, dire->dir);

		_strcat(temp, "/");

		_strcat(temp, command);

		if (stat(temp, &str) == 0)
		{
			freelist(head);
			return (temp);
		}

		dire = dire->next;
		free(temp);
	}

	freelist(head);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int x;
        int le = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;

	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (path[x + 1] == ':' || x == 0 || path[x + 1] == '\0')
			{
				le += _strlen(pwd) + 1;
			}
			else
			{
				le++;
			}
		}
		else
		{
			le++;
		}
	}

	path_copy = malloc(sizeof(char) * (le + 1));

	if (!path_copy)
	{
		return (NULL);
	}

	path_copy[0] = '\0';

	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (x == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[x + 1] == ':' || path[x + 1] == '\0')
			{
				_strcat(path_copy, ":");

				_strcat(path_copy, pwd);
			}
			else
			{
				_strcat(path_copy, ":");
			}
		}
		else
		{
			_strncat(path_copy, &path[x], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	char **dirs;
        char *path_cpy;
	int x;
	list_t *head = NULL;

	path_cpy = fill_path_dir(path);

	if (!path_cpy)
	{
		return (NULL);
	}

	dirs = _strtok(path_cpy, ":");

	free(path_cpy);

	if (!dirs)
	{
		return (NULL);
	}

	for (x = 0; dirs[x]; x++)
	{
		if (addnode_end(&head, dirs[x]) == NULL)
		{
			freelist(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
