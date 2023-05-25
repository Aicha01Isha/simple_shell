#include "shell.h"

/**
 * interactive - function that returns true if shell is interactive mode
 * @info: parameter
 * Return: 1 on suceess, 0 on failure
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->rd <= 2);
}

/**
 * is_delim - function checks if character is a delimeter
 * @c: parameter
 * @delim: parameter
 * Return: 1 on success, 0 on failure
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - function that checks for alphabetic character
 * @c: parameter
 * Return: 1 on success, 0 on failure
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - function that converts a string to an integer
 * @s: parameter
 * Return: 0 on success
 */

int _atoi(char *s)
{
	int a, si = 1, fla = 0, outpt;
	unsigned int res = 0;

	for (a = 0; s[a] != '\0' && fla != 2; a++)
	{
		if (s[a] == '-')
			si *= -1;
		if (s[a] >= '0' && s[a] <= '9')
		{
			fla = 1;
			res *= 10;
			res += (s[a] - '0');
		}
		else if (fla == 1)
			fla = 2;
	}
	if (si == -1)
		outpt = -res;
	else
		outpt = res;
	return (outpt);
}
