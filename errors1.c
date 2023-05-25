#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer
 * @s: parameter
 * Return: 0 on succes, -1 on failure
 */

int _erratoi(char *s)
{
	int a = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			res *= 10;
			res += (s[a] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - function that prints an error message
 * @info: parameter
 * @estr: parameter
 * Return: 0 on success, -1 on failure
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fna);
	_eputs(": ");
	print_d(info->line_cnt, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->arv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function that prints a decimal number
 * @input: parameter
 * @fd: parameter
 * Return: cnt
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, cnt = 0;
	unsigned int _ab_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_ab_ = -input;
		__putchar('-');
		cnt++;
	}
	else
		_ab_ = input;
	curr = _ab_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_ab_ / a)
		{
			__putchar('0' + curr / a);
			cnt++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	cnt++;
	return (cnt);
}

/**
 * convert_number - function that converter function
 * @num: parameter
 * @base: parameter
 * @flags: parameter
 * Return: pt
 */

char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char si = 0;
	char *pt;
	unsigned long i = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		i = -num;
		si = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buff[49];
	*pt = '\0';
	do	{
		*--pt = arr[i % base];
		i /= base;
	} while (i != 0);

	if (si)
		*--pt = si;
	return (pt);
}

/**
 * remove_comments - function that  replaces first instance of '#' with '\0'
 * @buf: parameter
 * Return: 0 on success
 */

void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
