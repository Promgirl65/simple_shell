#include "shell.h"

/**
* _strcpy - to copy string.
* @new: destination of copied string.
* @old: source of copied string.
*
* Return: pointer to destination
*/

char *_strcpy(char *new, char *old)
{
	int n = 0;

	if (new == old || old == 0)
		return (old);
	while (old[n])
	{
		new[n] = old[n];
		n++;
	}
	new[n] = 0;
	return (new);
}

/**
* _strdup - to duplicate string.
* @str: string to duplicate.
*
* Return: pointer to the duplicated string
*/

char *_strdup(const char *str)
{
	char *dup;
	int len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	for (len++; len--;)
		dup[len] = *--str;
	return (dup);
}

/**
* _puts - prints input string.
* @str: string to printed.
*
* Return: Nothing
*/

void _puts(char *str)
{
	int s = 0;

	if (!str)
		return;
	while (str[s] != '\0')
	{
		_putchar(str[s]);
		s++;
	}
}

/**
* _putchar - writes character c to the stdout.
* @c: character to print.
*
* Return: 1 (success), -1 (error) and errno is set.
*/

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
