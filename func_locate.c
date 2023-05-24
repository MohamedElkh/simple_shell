#include "shell.h"

list_t *getpath_dir(char *path);
char *fill_path_dir(char *path);

/**
 * getlocation - Locates a command in the PATH.
 * @commands: the command to locate.
 *
 * Return: if an error occurs or the command cannot be located - NULL.
 */

char *getlocation(char *commands)
{
	list_t *dire, *head;
	struct stat str;
	char **p, *temp;

	p = _getenv("PATH");

	if (!p || !(*p))
	{
		return (NULL);
	}

	dire = getpath_dir(*p + 5);

	head = dire;

	while (dire)
	{
		temp = malloc(_strlen(dire->dir) + _strlen(commands) + 2);

		if (!temp)
		{
			return (NULL);
		}

		_strcpy(temp, dire->dir);

		_strcat(temp, "/");

		_strcat(temp, commands);

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
 * fillpath_dir - func to Copies path but also replaces leading/sandwiched/
 * @paths: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 */

char *fillpath_dir(char *paths)
{
	int x;
	int le = 0;
	char *path_cpy, *pwd;

	pwd = *(_getenv("PWD")) + 4;

	for (x = 0; paths[x]; x++)
	{
		if (paths[x] == ':')
		{
			if (paths[x + 1] == ':' || x == 0 || paths[x + 1] == '\0')
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

	path_cpy = malloc(sizeof(char) * (le + 1));

	if (!path_cpy)
	{
		return (NULL);
	}

	path_cpy[0] = '\0';

	for (x = 0; paths[x]; x++)
	{
		if (paths[x] == ':')
		{
			if (x == 0)
			{
				_strcat(path_cpy, pwd);
				_strcat(path_cpy, ":");
			}
			else if (paths[x + 1] == ':' || paths[x + 1] == '\0')
			{
				_strcat(path_cpy, ":");

				_strcat(path_cpy, pwd);
			}
			else
			{
				_strcat(path_cpy, ":");
			}
		}
		else
		{
			_strncat(path_cpy, &paths[x], 1);
		}
	}
	return (path_cpy);
}

/**
 * getpath_dir - func to Tokenizes a colon-separated list of
 * @paths: colon-separated list of directories.
 *
 * Return: pointer to the initialized
 */

list_t *getpath_dir(char *paths)
{
	char **dirs;
	char *path_cpy;
	int x;
	list_t *head = NULL;

	path_cpy = fillpath_dir(paths);

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
