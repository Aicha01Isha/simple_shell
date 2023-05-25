#include "shell.h"

/**
 * _eputs - function that prints an input string
 * @str: parameter
 * Return: 0 on success
 */

void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - function that writes the character c to stderr
 * @c: parameter
 * Return: 1 on success, -1 on failure
 */

int _eputchar(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}
/**
 * _putfd - function that writes the character c to given fd
 * @c: parameter
 * @fd: parameter
 * Return: 1 on success, -1 on failure
 */

int _putfd(char c, int fd)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * _putsfd - function that prints an input string
 * @str: parameter
 * @fd: parameter
 * Return: a
 */

int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
