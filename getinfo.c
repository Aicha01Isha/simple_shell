#include "shell.h"

/**
 * clear_info - function that initializes info_t struct
 * @info: parameter
 */

void clear_info(info_t *info)
{
	info->ar = NULL;
	info->arv = NULL;
	info->pa = NULL;
	info->arc = 0;
}

/**
 * set_info - function that initializes info_t struct
 * @info: parameter
 * @av: parameter
 */

void set_info(info_t *info, char **av)
{
	int a = 0;

	info->fna = av[0];
	if (info->ar)
	{
		info->arv = strtow(info->ar, " \t");
		if (!info->arv)
		{
			info->arv = malloc(sizeof(char *) * 2);
			if (info->arv)
			{
				info->arv[0] = _strdup(info->ar);
				info->arv[1] = NULL;
			}
		}
		for (a = 0; info->arv && info->arv[a]; a++)
			;
		info->arc = a;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - function that frees info_t struct fields
 * @info: parameter
 * @all: parameter
 */

void free_info(info_t *info, int all)
{
	ffree(info->arv);
	info->arv = NULL;
	info->pa = NULL;
	if (all)
	{
		if (!info->cm_bu)
			free(info->ar);
		if (info->en)
			free_list(&(info->en));
		if (info->his)
			free_list(&(info->his));
		if (info->al)
			free_list(&(info->al));
		ffree(info->env);
			info->env = NULL;
		bfree((void **)info->cm_bu);
		if (info->rd > 2)
			close(info->rd);
		_putchar(BUF_FLUSH);
	}
}
