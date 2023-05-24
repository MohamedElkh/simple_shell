#include "shell.h"


void freealias_list(alias_t *main);
list_t *addnode_end(list_t **main, char *dire);
void freelist(list_t *main);
alias_t *addalias_end(alias_t **main, char *name, char *val);

/**
 * addalias_end - func to Adds a node to the end of a alias_t linked list.
 * @main: pointer to the head of the list_t list.
 * @name: name of the new alias to be added.
 * @val: value of the new alias to be added.
 *
 * Return: If - NULL.
 */
alias_t *addalias_end(alias_t **main, char *name, char *val)
{
	alias_t *new_v = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_v)
	{
		return (NULL);
	}

	new_v->next = NULL;
	new_v->name = malloc(sizeof(char) * (_strlen(name) + 1));

	if (!new_v->name)
	{
		free(new_v);

		return (NULL);
	}
	new_v->value = val;

	_strcpy(new_v->name, name);

	if (*main)
	{
		last = *main;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_v;
	}
	else
	{
		*main = new_v;
	}

	return (new_v);
}

/**
 * addnode_end - func to Adds a node to the end of a list_t linked list.
 * @main: the head of the list_t list.
 * @dire: directory path for the new node to contain.
 *
 * Return: if an error occurs - NULL.
 */

list_t *addnode_end(list_t **main, char *dire)
{
	list_t *new_v = malloc(sizeof(list_t));

	list_t *lastt;

	if (!new_v)
	{
		return (NULL);
	}

	new_v->dir = dire;
	new_v->next = NULL;

	if (*main)
	{
		lastt = *main;
		while (lastt->next != NULL)
		{
			lastt = lastt->next;
		}

		lastt->next = new_v;
	}
	else
	{
		*main = new_v;
	}

	return (new_v);
}

/**
 * freealias_list - Frees a alias_t linked list.
 * @main: the head of the alias_t list.
 */

void freealias_list(alias_t *main)
{

	alias_t *nex;

	while (main)
	{
		nex = main->next;
		free(main->name);

		free(main->value);
		free(main);
		main = nex;
	}
}

/**
 * freelist - Frees a list_t linked list.
 * @main: The head of the list_t list.
 */
void freelist(list_t *main)
{
	list_t *nex;

	while (main)
	{
		nex = main->next;
		free(main->dir);

		free(main);
		main = nex;
	}
}
