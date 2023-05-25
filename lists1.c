#include "shell.h"

/**
 * list_len - function that determines length of linked list
 * @h: parameter
 * Return: a
 */

size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - function that returns an array of strings
 * @head: parameter
 * Return: sts
 */

char **list_to_strings(list_t *head)
{
	list_t *nod = head;
	size_t a = list_len(head), b;
	char **sts;
	char *st;

	if (!head || !a)
		return (NULL);
	sts = malloc(sizeof(char *) * (a + 1));
	if (!sts)
		return (NULL);
	for (a = 0; nod; nod = nod->next, a++)
	{
		st = malloc(_strlen(nod->str) + 1);
		if (!st)
		{
			for (b = 0; b < a; b++)
				free(sts[b]);
			free(sts);
			return (NULL);
		}
		st = _strcpy(st, nod->str);
		sts[a] = st;
	}
	sts[a] = NULL;
	return (sts);
}


/**
 * print_list - function that prints all elements of a list_t linked list
 * @h: parameter
 * Return: a
 */

size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - function that returns node
 * @node: parameter
 * @prefix: parameter
 * @c: parameter
 * Return: null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *n = NULL;

	while (node)
	{
		n = starts_with(node->str, prefix);
		if (n && ((c == -1) || (*n == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - function that gets the index of a node
 * @head: parameter
 * @node: parameter
 * Return: -1 on success
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
