#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: parameter
 * Return: exits
 */

int _myexit(info_t *info)
{
	int exch;

	if (info->arv[1])
	{
		exch = _erratoi(info->arv[1]);
		if (exch == -1)
		{
			info->stat = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->arv[1]);
			_eputchar('\n');
			return (1);
		}
		info->er_nu = _erratoi(info->arv[1]);
		return (-2);
	}
	info->er_nu = -1;
	return (-2);
}

/**
 * _mycd - function that changes the current directory of the process
 * @info: parameter
 * Return: 0 on success
 */

int _mycd(info_t *info)
{
	char *a, *d, buff[1024];
	int chd_rt;

	a = getcwd(buff, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arv[1])
	{
		d = _getenv(info, "HOME=");
		if (!d)
			chd_rt =
				chdir((d = _getenv(info, "PWD=")) ? d : "/");
		else
			chd_rt = chdir(d);
	}
	else if (_strcmp(info->arv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chd_rt =
			chdir((d = _getenv(info, "OLDPWD=")) ? d : "/");
	}
	else
		chd_rt = chdir(info->arv[1]);
	if (chd_rt == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->arv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - function that changes the current directory of the process
 * @info: parameter
 * Return: 0 on sucess
 */

int _myhelp(info_t *info)
{
	char **ar_arr;

	ar_arr = info->arv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ar_arr);
	return (0);
}
