#include "shell.h"

/**
 * _myhistory - function that displays the history list
 * @info: parameter
 *  Return: 0 on success
 */

int _myhistory(info_t *info)
{
	print_list(info->his);
	return (0);
}

/**
 * unset_alias - function that sets alias to string
 * @info: parameter
 * @str: parameter
 * Return: 0 on success, 1 on failure
 */

int unset_alias(info_t *info, char *str)
{
	char *b, a;
	int r;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	a = *b;
	*b = 0;
	r = delete_node_at_index(&(info->al),
		get_node_index(info->al, node_starts_with(info->al, str, -1)));
	*b = a;
	return (r);
}

/**
 * set_alias - function that sets alias to string
 * @info: parameter
 * @str: parameter
 * Return: 0 on success, 1 on failure
 */

int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->al), str, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @node: parameter
 * Return: 0 on success, 1 on failure
 */

int print_alias(list_t *node)
{
	char *b = NULL, *i = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (i = node->str; i <= b; i++)
		_putchar(*i);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function that mimics the alias builtin
 * @info: parameter
 * Return: 0 on success
 */

int _myalias(info_t *info)
{
	int a = 0;
	char *b = NULL;
	list_t *nod = NULL;

	if (info->arc == 1)
	{
		nod = info->al;
		while (nod)
		{
			print_alias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (a = 1; info->arv[a]; a++)
	{
		b = _strchr(info->arv[a], '=');
		if (b)
			set_alias(info, info->arv[a]);
		else
			print_alias(node_starts_with(info->al, info->arv[a], '='));
	}
	return (0);
}
