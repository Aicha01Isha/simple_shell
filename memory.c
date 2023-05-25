#include "shell.h"

/**
 * bfree - function that frees a pointer and NULLs the address
 * @ptr: parameter
 * Return: 1 on success, 0 on failure
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
