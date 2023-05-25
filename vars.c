#include "shell.h"

/**
 * is_chain - function that test the current char in bffer
 * @info: parameter
 * @buf: parameter
 * @p: parameter
 * Return: 1 on success, 0 on failure
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t b = *p;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		info->cm_bu_ty = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		info->cm_bu_ty = CMD_AND;
	}
	else if (buf[b] == ';')
	{
		buf[b] = 0;
		info->cm_bu_ty = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - function that checks if we should continue
 * @info: parameter
 * @buf: parameter
 * @p: parameter
 * @i: parameter
 * @len: parameter
 * Return: nothing
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (info->cm_bu_ty == CMD_AND)
	{
		if (info->stat)
		{
			buf[i] = 0;
			b = len;
		}
	}
	if (info->cm_bu_ty == CMD_OR)
	{
		if (!info->stat)
		{
			buf[i] = 0;
			b = len;
		}
	}
	*p = b;
}

/**
 * replace_alias - function that replaces an aliases in the tokenized string
 * @info: parameter
 * Return: 1 on success, 0 on failure
 */

int replace_alias(info_t *info)
{
	int a;
	list_t *nod;
	char *n;

	for (a = 0; a < 10; a++)
	{
		nod = node_starts_with(info->al, info->arv[0], '=');
		if (!nod)
			return (0);
		free(info->arv[0]);
		n = _strchr(nod->str, '=');
		if (!n)
			return (0);
		n = _strdup(n + 1);
		if (!n)
			return (0);
		info->arv[0] = n;
	}
	return (1);
}

/**
 * replace_vars - function that replaces vars in the tokenized string
 * @info: parameter
 * Return: 0 on success, 1 on failure
 */

int replace_vars(info_t *info)
{
	int a = 0;
	list_t *nod;

	for (a = 0; info->arv[a]; a++)
	{
		if (info->arv[a][0] != '$' || !info->arv[a][1])
			continue;
		if (!_strcmp(info->arv[a], "$?"))
		{
			replace_string(&(info->arv[a]),
					_strdup(convert_number(info->stat, 10, 0)));
			continue;
		}
		if (!_strcmp(info->arv[a], "$$"))
		{
			replace_string(&(info->arv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nod = node_starts_with(info->en, &info->arv[a][1], '=');
		if (nod)
		{
			replace_string(&(info->arv[a]),
					_strdup(_strchr(nod->str, '=') + 1));
			continue;
		}
		replace_string(&info->arv[a], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - function that replaces string
 * @old: parameter
 * @new: parameter
 * Return: 1 on success, 0 on failure
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
