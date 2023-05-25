#include "shell.h"

/**
 * _memset - function that fills memory with a constant byte
 * @s: parameter
 * @b: parameter
 * @n: parameter
 * Return: s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - function that frees a string of strings
 * @pp: parameter
 */

void ffree(char **pp)
{
	char **i = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(i);
}

/**
 * _realloc - function that reallocates a block of memory
 * @ptr: parameter
 * @old_size: parameter
 * @new_size: parameter
 * Return: n
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *n;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	n = malloc(new_size);
	if (!n)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		n[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (n);
}
