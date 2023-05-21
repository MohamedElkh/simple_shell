#include "shell.h"


void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);
alias_t *add_alias_end(alias_t **head, char *name, char *value);

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
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
	new_v->value = value;

	_strcpy(new_v->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new_v;
	}
	else
	{
		*head = new_v;
	}

	return (new_v);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_v = malloc(sizeof(list_t));

	list_t *lastt;

	if (!new_v)
	{
		return (NULL);
	}

	new_v->dir = dir;
	new_v->next = NULL;

	if (*head)
	{
		lastt = *head;
		while (lastt->next != NULL)
		{
			lastt = lastt->next;
		}

		lastt->next = new_v;
	}
	else
	{
		*head = new_v;
	}

	return (new_v);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head)
{

	alias_t *nex;

	while (head)
	{
		nex = head->next;
		free(head->name);

		free(head->value);
		free(head);
		head = nex;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *nex;

	while (head)
	{
		nex = head->next;
		free(head->dir);

		free(head);
		head = nex;
	}
}
