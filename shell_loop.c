#include "shell.h"

/**
 * hsh - main function for  shell loop
 * @info: parameter
 * @av: parameter
 * Return: 0 on success, 1 on failure
 */

int hsh(info_t *info, char **av)
{
	ssize_t a = 0;
	int bltn_ret = 0;

	while (a != -1 && bltn_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		a = get_input(info);
		if (a != -1)
		{
			set_info(info, av);
			bltn_ret = find_builtin(info);
			if (bltn_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->stat)
		exit(info->stat);
	if (bltn_ret == -2)
	{
		if (info->er_nu == -1)
			exit(info->stat);
		exit(info->er_nu);
	}
	return (bltn_ret);
}

/**
 * find_builtin - function that finds a builtin command
 * @info: parameter
 * Return: 0 on success
 */

int find_builtin(info_t *info)
{
	int a, blt_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->arv[0], builtintbl[a].type) == 0)
		{
			info->line_cnt++;
			blt_in_ret = builtintbl[a].func(info);
			break;
		}
	return (blt_in_ret);
}

/**
 * find_cmd - function that finds a command in PATH
 * @info: parameter
 * Return: nothing
 */

void find_cmd(info_t *info)
{
	char *p = NULL;
	int a, b;

	info->pa = info->arv[0];
	if (info->linecnt_flg == 1)
	{
		info->line_cnt++;
		info->linecnt_flg = 0;
	}
	for (a = 0, b = 0; info->ar[a]; a++)
		if (!is_delim(info->ar[a], " \t\n"))
			b++;
	if (!b)
		return;
	p = find_path(info, _getenv(info, "PATH="), info->arv[0]);
	if (p)
	{
		info->pa = p;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->arv[0][0] == '/') && is_cmd(info, info->arv[0]))
			fork_cmd(info);
		else if (*(info->ar) != '\n')
		{
			info->stat = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - function forks a an exec thread to run cmd
 * @info: parameter
 * Return: nothinf
 */

void fork_cmd(info_t *info)
{
	pid_t chld_pd;

	chld_pd = fork();
	if (chld_pd == -1)
	{
		perror("Error:");
		return;
	}
	if (chld_pd == 0)
	{
		if (execve(info->pa, info->arv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->stat));
		if (WIFEXITED(info->stat))
		{
			info->stat = WEXITSTATUS(info->stat);
			if (info->stat == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
