#include "shell.h"

/**
 * _memset - fills the memory block.
 * @m: points to the memory.
 * @f: fills pointer m.
 * @count: the size of memoryto fill.
 * Return: m
 */

char *_memset(char *m, char f, unsigned int count)
{
	unsigned int n;

	for (n = 0; n < count; n++)
	{
		m[n] = f;
	}

	return (m);
}

/**
 * bfree - to free pointer and address becomes NULL.
 * @ptr: the address of pointer.
 *
 * Return 1(success), 0(fail).
 */

int bfree(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	else
		return (0);
}

/**
 * free_str - free string
 * @s: string
 */

void free_str(char **s)
{
	char **c = s;

	if (s == 0)
	{
		return;
	}
	while (*s)
		free(*s++);
	free(c);
}

/**
 * *_realloc - to reallocate the memory block.
 * @mem_siz1: initial memory size of block.
 * @mem_siz2: new memory size of block.
 * @ptr: pointer to initial block.
 *
 * Return: a (pointer to block).
 */

void *_realloc(void *ptr, unsigned int mem_siz1, unsigned int mem_siz2)
{
	char *a;

	if (ptr == 0)
	{
		return (malloc(mem_siz2));
	}
	if (mem_siz2 == 0)
	{
		return (free(ptr), NULL);
	}
	if (mem_siz2 == mem_siz1)
	{
		return (ptr);
	}
	a = malloc(mem_siz2);

	if (a == 0)
	{
		return (NULL);
	}

	if (mem_siz1 > mem_siz2)
	{
		mem_siz1 = mem_siz1;
	}

	while (mem_siz1--)
		a[mem_siz1] = ((char *)ptr)[mem_siz1];
	free(ptr);
	return (a);
}
