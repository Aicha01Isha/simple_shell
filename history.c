#include "shell.h"

/**
 * get_history_file - function that gets the history file
 * @info: parameter
 * Return: buff
 */

char *get_history_file(info_t *info)
{
	char *buff, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, d);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - function that creates a file
 * @info: parameter
 * Return: 1 on success, -1 on failure
 */

int write_history(info_t *info)
{
	ssize_t f;
	char *fn = get_history_file(info);
	list_t *nod = NULL;

	if (!fn)
		return (-1);
	f = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (f == -1)
		return (-1);
	for (nod = info->his; nod; nod = nod->next)
	{
		_putsfd(nod->str, f);
		_putfd('\n', f);
	}
	_putfd(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * read_history - function that reads history from file
 * @info: parameter
 * Return: histcnt on success, 0 on failure
 */

int read_history(info_t *info)
{
	int a, l = 0, lncnt = 0;
	ssize_t fd, rdl, fs = 0;
	struct stat st;
	char *buff = NULL, *fn = get_history_file(info);

	if (!fn)
		return (0);
	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	buff = malloc(sizeof(char) * (fs + 1));
	if (!buff)
		return (0);
	rdl = read(fd, buff, fs);
	buff[fs] = 0;
	if (rdl <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < fs; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			build_history_list(info, buff + l, lncnt++);
			l = a + 1;
		}
	if (l != a)
		build_history_list(info, buff + l, lncnt++);
	free(buff);
	info->histcnt = lncnt;
	while (info->histcnt-- >= HIST_MAX)
		delete_node_at_index(&(info->his), 0);
	renumber_history(info);
	return (info->histcnt);
}

/**
 * build_history_list - function that adds entry to a history linked list
 * @info: parameter
 * @buf: parameter
 * @linecount: parameter
 * Return: 0 on success
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nod = NULL;

	if (info->his)
		nod = info->his;
	add_node_end(&nod, buf, linecount);

	if (!info->his)
		info->his = nod;
	return (0);
}

/**
 * renumber_history - function that renumbers the history linked list
 * @info: parameter
 * Return: a
 */

int renumber_history(info_t *info)
{
	list_t *nod = info->his;
	int a = 0;

	while (nod)
	{
		nod->num = a++;
		nod = nod->next;
	}
	return (info->histcnt = a);
}
