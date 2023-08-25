#include "shell.h"

/**
* bfree -its free a pointer and NULLs the address.
* @ptr:the address of the pointer to free.
*
* Return: 1 if freed, Otherwise 0.
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
