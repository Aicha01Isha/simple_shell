#include "shell.h"

/**
 * get_environ - function that returns the string array copy of our environ
 * @info: parameter
 * Return: 0 on success
 */

char **get_environ(info_t *info)
{
	if (!info->env || info->env_chng)
	{
		info->env = list_to_strings(info->en);
		info->env_chng = 0;
	}
	return (info->env);
}

/**
 * _unsetenv - function that removes an environment variable
 * @info: parameter
 * @var: parameter
 * Return: 1 on success, 0 on failure
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *nod = info->en;
	size_t a = 0;
	char *n;

	if (!nod || !var)
		return (0);
	while (nod)
	{
		n = starts_with(nod->str, var);
		if (n && *n == '=')
		{
			info->env_chng = delete_node_at_index(&(info->en), a);
			a = 0;
			nod = info->en;
			continue;
		}
		nod = nod->next;
		a++;
	}
	return (info->env_chng);
}

/**
 * _setenv - function that initialize a new envirenment
 * @info: parameter
 * @var: parameter
 * @value: parameter
 *  Return: 0 on success
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *nod;
	char *n;

	if (!var || !value)
		return (0);
	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	nod = info->en;
	while (nod)
	{
		n = starts_with(nod->str, var);
		if (n && *n == '=')
		{
			free(nod->str);
			nod->str = buff;
			info->env_chng = 1;
			return (0);
		}
		nod = nod->next;
	}
	add_node_end(&(info->en), buff, 0);
	free(buff);
	info->env_chng = 1;
	return (0);
}
