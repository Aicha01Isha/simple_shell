#include "shell.h"

/**
 * **strtow - function that splits a string into words
 * @str: parameter
 * @d: parameter
 * Return: n
 */

char **strtow(char *str, char *d)
{
	int a, b, c, m, nuwrds = 0;
	char **n;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			nuwrds++;
	if (nuwrds == 0)
		return (NULL);
	n = malloc((1 + nuwrds) * sizeof(char *));
	if (!n)
		return (NULL);
	for (a = 0, b = 0; b < nuwrds; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		n[b] = malloc((c + 1) * sizeof(char));
		if (!n[b])
		{
			for (c = 0; c < b; c++)
				free(n[c]);
			free(n);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			n[b][m] = str[a++];
		n[b][m] = 0;
	}
	n[b] = NULL;
	return (n);
}

/**
 * **strtow2 - function that splits a string into words
 * @str: parameter
 * @d: parameter
 * Return: n
 */

char **strtow2(char *str, char d)
{
	int a, b, c, m, nuwrds = 0;
	char **n;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			nuwrds++;
	if (nuwrds == 0)
		return (NULL);
	n = malloc((1 + nuwrds) * sizeof(char *));
	if (!n)
		return (NULL);
	for (a = 0, b = 0; b < nuwrds; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		n[b] = malloc((c + 1) * sizeof(char));
		if (!n[b])
		{
			for (c = 0; c < b; c++)
				free(n[c]);
			free(n);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			n[b][m] = str[a++];
		n[b][m] = 0;
	}
	n[b] = NULL;
	return (n);
}
