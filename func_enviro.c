#include "shell.h"


void free_enve(void);
char **_getenv(const char *vari);
char **_copyenve(void);

/**
 * _copyenve - func to Creates a copy of the environment.
 *
 * Return: if the error occurs - NULL.
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
 * _getenv - func to Gets an environmental variable
 * @vari: name of the environmental variable .
 *
 * Return: If the environmental variable does not exist - NULL.
 */

char **_getenv(const char *vari)
{
	int i;
	int l;

	l = _strlen(vari);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(vari, environ[i], l) == 0)
		{
			return (&environ[i]);
		}
	}

	return (NULL);
}


/**
 * free_enve - the frees the the environment copy.
 *
 * Return: nothing.
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

