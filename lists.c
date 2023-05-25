#include "shell.h"

/**
 * add_node - function that adds a node to the start of the list
 * @head: parameter
 * @str: parameter
 * @num: parameter
 * Return: head
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_node_end - function that adds a node to the end of the list
 * @head: parameter
 * @str: parameter
 * @num: parameter
 * Return: node
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nod, *nod;

	if (!head)
		return (NULL);
	nod = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	_memset((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = num;
	if (str)
	{
	new_nod->str = _strdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_list_str - function that prints only the str element
 * @h: parameter
 * Return: a
 */

size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - function that deletes node at given index
 * @head: parameter
 * @index: parameter
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nod, *pr_nod;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		nod = *head;
		*head = (*head)->next;
		free(nod->str);
		free(nod);
		return (1);
	}
	nod = *head;
	while (nod)
	{
		if (a == index)
		{
			pr_nod->next = nod->next;
			free(nod->str);
			free(nod);
			return (1);
		}
		a++;
		pr_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * free_list - function that frees all nodes of a list
 * @head_ptr: parameter
 * Return: null
 */

void free_list(list_t **head_ptr)
{
	list_t *nod, *next_nod, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	nod = h;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->str);
		free(nod);
		nod = next_nod;
	}
	*head_ptr = NULL;
}
