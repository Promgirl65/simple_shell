#include "shell.h"

/**
 * _putchar - writes a char.
 * @c: char to print.
 *
 * Return: 1 (success) or -1 (error), errno is set.
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
		buf[i = i + 1] = c;
	return (1);
}

/**
 * _strlen - string length.
 * @str: string length to check.
 *
 * Return: len (length of string)
 */

int _strlen(char *str)
{
	int n = 0;

	if (!str)
	{
		return (0);
	}
	while (*str++)
		n = n + 1;
	return (n);
}

/**
 * _strcmp - compare two strings.
 * @str_1: first string.
 * @str_2: second string.
 *
 * Return: (-) if s1 < s2; (+) if s1 > s2; (0) if s1 == s2
 */

int _strcmp(char *str_1, char *str_2)
{
	while (*str_1 && *str_2)
	{
		if (*str_1 != *str_2)
			return (*str_1 - *str_2);
		str_1++;
		str_2++;
	}
	if (*str_1 == *str_2)
		return (0);
	else
		return (*str_1 < *str_2 ? -1 : 1);
}

/**
 * starts_with - to check if needle starts with haystack.
 * @haystack: the string to search.
 * @needle: substring to search.
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - to concatenate strings
 * @new: the destination buffer
 * @old: the source buffer
 *
 * Return: id (pointer to new)
 */

char *_strcat(char *new, char *old)
{
	char *id = new;

	while (*new)
		new++;
	while (*old)
		*new++ = *old++;
	*new = *old;
	return (id);
}
