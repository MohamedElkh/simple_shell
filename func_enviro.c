#include "shell.h"


void free_enve(void);
char **_getenv(const char *var);
char **_copyenve(void);

/**
 * _copyenve - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenve(void)
{
	size_t size;
	char **new_enviro;
	int i;

	for (size = 0; environ[size]; size++)
	{
		;
	}

	new_enviro = malloc(sizeof(char *) * (size + 1));

	if (!new_enviro)
	{
		return (NULL);
	}

	for (i = 0; environ[i]; i++)
	{
		new_enviro[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_enviro[i])
		{
			for (i--; i >= 0; i--)
			{
				free(new_enviro[i]);
			}
			free(new_enviro);
			return (NULL);
		}
		_strcpy(new_enviro[i], environ[i]);
	}
	new_enviro[i] = NULL;

	return (new_enviro);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int i;
	int l;

	l = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], l) == 0)
		{
			return (&environ[i]);
		}
	}

	return (NULL);
}


/**
 * free_enve - Frees the the environment copy.
 */
void free_enve(void)
{
	int x;

	for (x = 0; environ[x]; x++)
	{
		free(environ[x]);
	}
	free(environ);
}

