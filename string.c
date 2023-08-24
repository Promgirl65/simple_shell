#include "shell.h"

/**
* _strlen - returns string length.
* @c: string length to check.
*
* Return: integer length of string
*/

int _strlen(char *c)
{
	int x = 0;

	if (!c)
		return (0);
	while (*c++)
		x++;
	return (x);
}

/**
* _strcmp - compares two strings.
* @str1: first string.
* @str2: second string.
*
* Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
*/

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
* starts_with - to check if needle starts with haystack.
* @haystack: the string to search.
* @needle: substring to search.
*
* Return: address of next haystack char or NULL
*/

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
* _strcat - to concatenate two strings.
* @new: destination buffer.
* @old: source buffer.
*
* Return: pointer to destination buffer
*/

char *_strcat(char *new, char *old)
{
	char *ret = new;

	while (*new)
		new++;
	while (*old)
		*new++ = *old++;
	*new = *old;
	return (ret);
}
