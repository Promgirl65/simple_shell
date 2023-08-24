#include "shell.h"

/**
* _memset - fills memory with constant byte.
* @s: points to the memory area.
* @b: byte to fill *s with.
* @n: number of bytes to be filled.
* Return: (s) a pointer to the memory area s
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
* ffree - frees string of strings.
* @pp: string of strings
*/

void ffree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}

/**
* _realloc - reallocates the block of memory.
* @ptr: pointer to previous malloc'ated block.
* @old: byte size of previous memory block.
* @new: byte size of new memory block.
*
* Return: pointer to the old block.
*/

void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
	char *c;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);
	c = malloc(new);
	if (!c)
		return (NULL);
	old = old < new ? old : new;
	while (old--)
		c[old] = ((char *)ptr)[old];
free(ptr);
return (c);
}
