#include "shell.h"

/**
 * is_cmd - function that determines if a file is an executable command
 * @info: parameter
 * @path: parameter
 * Return: 1 on success, 0 on failure
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function that duplicates characters
 * @pathstr: parameter
 * @start: parameter
 * @stop: parameter
 * Return: buff
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buff[b++] = pathstr[a];
	buff[b] = 0;
	return (buff);
}

/**
 * find_path - function that finds this cmd in the PATH string
 * @info: parameter
 * @pathstr: parameter
 * @cmd: parameter
 * Return: NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, cur_p = 0;
	char *pa;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			pa = dup_chars(pathstr, cur_p, a);
			if (!*pa)
				_strcat(pa, cmd);
			else
			{
				_strcat(pa, "/");
				_strcat(pa, cmd);
			}
			if (is_cmd(info, pa))
				return (pa);
			if (!pathstr[a])
				break;
			cur_p = a;
		}
		a++;
	}
	return (NULL);
}
