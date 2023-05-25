#include "shell.h"

/**
 * _strcpy - function that copies a string
 * @dest: parameter
 * @src: parameter
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - function that duplicates a string
 * @str: parameter
 * Return: r
 */

char *_strdup(const char *str)
{
	int lgth = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lgth++;
	r = malloc(sizeof(char) * (lgth + 1));
	if (!r)
		return (NULL);
	for (lgth++; lgth--;)
		r[lgth] = *--str;
	return (r);
}

/**
 * _puts - function that prints an input string
 * @str:parameter
 * Return: 0 on success
 */

void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - function that writes the character c to stdout
 * @c: parameter
 * Return: 1 on success, -1 on failure
 */

int _putchar(char c)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buff[a++] = c;
	return (1);
}
