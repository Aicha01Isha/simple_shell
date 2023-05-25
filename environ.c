#include "shell.h"

/**
 * _myenv - function that prints the current environment
 * @info: parameter
 * Return: 0 on success
 */

int _myenv(info_t *info)
{
	print_list_str(info->en);
	return (0);
}

/**
 * _getenv - function that gets the value of an environement
 * @info: parameter
 * @name: parameter
 * Return: null
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *nod = info->en;
	char *b;

	while (nod)
	{
		b = starts_with(nod->str, name);
		if (b && *b)
			return (b);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * _mysetenv - function that initialize or modify a new envirenemnt
 * @info: parameter
 *  Return: 0 on success
 */

int _mysetenv(info_t *info)
{
	if (info->arc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->arv[1], info->arv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function that remove an environment variable
 * @info: parameter
 * Return: 0 on success
 */

int _myunsetenv(info_t *info)
{
	int a;

	if (info->arc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->arc; a++)
		_unsetenv(info, info->arv[a]);
	return (0);
}

/**
 * populate_env_list - function that populates env linked list
 * @info: parameter
 * Return: 0 on success
 */

int populate_env_list(info_t *info)
{
	list_t *nod = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&nod, environ[a], 0);
	info->en = nod;
	return (0);
}
