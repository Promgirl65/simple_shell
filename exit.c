#include "shell.h"

/**
 * _strncpy - copies the string.
 * @new: destination of copied string.
 * @old: source of copied string.
 * @num: number of characters copied.
 *
 * Return: the concatenated string.
 */

char *_strncpy(char *new, char *old, int num)
{
	int i, j;
	char *s = new;
	i = 0;
	while (old[i] != '\0' && i < num - 1)
	{
		new[i] = old[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			new[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - concatenates two strings.
 * @new: first string.
 * @old: second string
 * @num: maximum number of bytes to be used.
 *
 * Return: the concatenated string
 */

char *_strncat(char *new, char *old, int num)
{
	int i, j;
	char *s = new;
	i = 0;
	j = 0;
	while (new[i] != '\0')
		i++;
	while (old[j] != '\0' && j < n)
	{
		new[i] = old[j];
		i++;
		j++;
	}
	if (j < n)
		new[i] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in the string.
 * s: string to be parsed.
 * @c: character to locate.
 *
 * Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
