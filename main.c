#include "shell.h"

/**
 * main - function that is the entry point
 * @ac: parameter
 * @av: parameter
 * Return: 0 on success, 1 on failure
 */

int main(int ac, char **av)
{
	info_t in[] = { INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		in->rd = f;
	}
	populate_env_list(in);
	read_history(in);
	hsh(in, av);
	return (EXIT_SUCCESS);
}
