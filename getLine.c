#include "shell.h"

/**
 * input_buf - function that buffers chained commands
 * @info: parameter
 * @buf: parameter
 * @len: parameter
 * Return: i
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t i = 0;
	size_t l_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		i = getline(buf, &l_p, stdin);
#else
		i = _getline(info, buf, &l_p);
#endif
		if (i > 0)
		{
			if ((*buf)[i - 1] == '\n')
			{
				(*buf)[i - 1] = '\0';
				i--;
			}
			info->linecnt_flg = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcnt++);
			{
				*len = i;
				info->cm_bu = buf;
			}
		}
	}
	return (i);
}

/**
 * get_input - function that gets a line minus the newline
 * @info: parameter
 * Return: i
 */

ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t a, b, l;
	ssize_t i = 0;
	char **buff_p = &(info->ar), *p;

	_putchar(BUF_FLUSH);
	i = input_buf(info, &buff, &l);
	if (i == -1)
		return (-1);
	if (l)
	{
		b = a;
		p = buff + a;
		check_chain(info, buff, &b, a, l);
		while (b < l)
		{
			if (is_chain(info, buff, &b))
				break;
			b++;
		}
		a = b + 1;
		if (a >= l)
		{
			a = l = 0;
			info->cm_bu_ty = CMD_NORM;
		}
		*buff_p = p;
		return (_strlen(p));
	}
	*buff_p = buff;
	return (i);
}

/**
 * read_buf - function that reads a buffer
 * @info: parameter
 * @buf: parameter
 * @i: parameter
 * Return: a
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
	return (0);
	a = read(info->rd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * _getline - function that gets the next line of input from STDIN
 * @info: parameter
 * @ptr: parameter
 * @length: parameter
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t a, l;
	size_t b;
	ssize_t r = 0, s = 0;
	char *n = NULL, *new_n = NULL, *c;

	n = *ptr;
	if (n && length)
		s = *length;
	if (a == l)
		a = l = 0;
	r = read_buf(info, buff, &l);
	if (r == -1 || (r == 0 && l == 0))
		return (-1);
	c = _strchr(buff + a, '\n');
	b = c ? 1 + (unsigned int)(c - buff) : l;
	new_n = _realloc(n, s, s ? s + b : b + 1);
	if (!new_n)
		return (n ? free(n), -1 : -1);
	if (s)
		_strncat(new_n, buff + a, b - a);
	else
	_strncpy(new_n, buff + a, b - a + 1);
	s += b - a;
	a = b;
	n = new_n;

	if (length)
		*length = s;
	*ptr = n;
	return (s);
}

/**
 * sigintHandler - function that blocks ctrl-C
 * @sig_num: parameter
 * Return: nothing
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
