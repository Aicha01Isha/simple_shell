#include "shell.h"

/**
 **_strncpy - function that copies a string
 *@dest: parameter
 *@src: parameter
 *@n: parameter
 *Return:p
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *p = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (p);
}

/**
 * *_strncat - function that concatenates two strings
 * @dest: parameter
 * @src: parameter
 * @n: parameter
 * Return: p
 */

char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *p = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (p);
}

/**
 * *_strchr - function that locates a character in a string
 * @s: parameter
 * @c: parameter
 * Return: null
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
