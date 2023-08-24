#include "shell.h"

/**
 * _strncpy -to copy the string.
 * @new: destination of copied string.
 * @old: source of copied string.
 * @num: number of characters in copied string.
 *
 * Return: c (copied string)
 */

char *_strncpy(char *new, char *old, int num)
{
	int i, k;
	char *c = new;

	i = 0;
	while (old[i] != '\0' && i < num - 1)
	{
		new[i] = old[i];
		i = i + 1;
	}
	if (i < num)
	{
		k = i;
		while (k < num)
		{
			new[k] = '\0';
			k++;
		}
	}
	return (c);
}

/**
 * _strncat - to concatenate strings.
 * @new: a string.
 * @old: a string.
 * @num: size of space.
 *
 * Return: c (concatenated string)
 */

char *_strncat(char *new, char *old, int num)
{
	int i = 0, k = 0;
	char *c = new;

	while (new[i] != '\0')
		i = i + 1;
	while (old[k] != '\0' && k < num)
	{
		new[i] = old[k];
		i = i + 1;
		k = k + 1;
	}
	if (k < num)
		new[i] = '\0';
	return (c);
}

/**
 * _strchr - to locate characters in a string.
 * @a: string to parse.
 * @b: character to locate.
 *
 * Return: a (parsed string)
 */

char *_strchr(char *a, char b)
{
	do
	{
		if (*a == b)
			return (a);
	}
	while (*a++ != '\0');

	return (NULL);
}

/**
 * _strcpy - to copy string.
 * @new: destination of copied string.
 * @old: source of copied string.
 *
 * Return: new
 */

char *_strcpy(char *new, char *old)
{
	int n = 0;

	if (new == old || old == 0)
		return (new);
	while (old[n])
	{
		new[n] = old[n];
		n = n + 1;
	}
	new[n] = 0;
	return (new);
}

/**
 * _strdup - to duplicate string.
 * @s: string to be duplicated.
 *
 * Return: dup (duplicated string)
 */

char *_strdup(const char *s)
{
	int i = 0;
	char *dup;

	if (s == NULL)
		return (NULL);
	while (*s++)
		i = i + 1;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	for (i++; i--;)
		dup[i] = *--s;
	return (dup);
}

/**
 * _puts - to print input string.
 * @s: the string to be printed
 */

void _puts(char *s)
{
	int n = 0;

	if (!s)
		return;
	while (s[n] != '\0')
	{
		_putchar(s[n]);
		n = n + 1;
	}
}
