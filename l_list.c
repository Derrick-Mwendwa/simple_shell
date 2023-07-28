#include "main.h"

/**
 * add_alias_e - adds a new node at the end of a list_t list
 * @head: pointer to the head of the list_t list
 * @name: name of the new alias to be added
 * @val: value of the new alias to be added
 *
 * Return: pointer to the new node or NULL if it failed
 */
alias *add_alias_e(alias **head, string name, string val)
{
	alias *n_node = malloc(sizeof(alias));
	alias *last;

	if (!n_node)
		return (NULL);

	n_node->next = NULL;
	n_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!n_node->name)
	{
		free(n_node);
		return (NULL);
	}
	n_node->val = val;
	_strcpy(n_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = n_node;
	}
	else
		*head = n_node;

	return (n_node);
}

/**
 * add_node_e - adds a new node at the end of a list_t list
 * @head: pointer to the head of the list_t list
 * @dir: dir of the new node to be added
 *
 * Return: pointer to the new node or NULL if it failed
 */
list_t *add_node_e(list_t **head, string dir)
{
	list_t *n_node = malloc(sizeof(list_t));
	list_t *last;

	if (!n_node)
		return (NULL);

	n_node->dir = dir;
	n_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = n_node;
	}
	else
		*head = n_node;

	return (n_node);
}

/**
 * free_alias_list - frees an alias_t linked list
 * @head: head of the alias_t linked list
 *
 * Return: void
 */
void free_alias_list(alias *head)
{
	alias *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->val);
		free(head);
		head = next;
	}
}

/**
 * free_list - frees a list_t linked list
 * @head: head of the list_t linked list
 *
 * Return: void
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
