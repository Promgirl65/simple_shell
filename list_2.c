#include "shell.h"

/**
 * list_len - length of linked list.
 * @h: points to first node of the linked list.
 *
 * Return: s (size)
 */
size_t list_len(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * list_to_strings - returns strings of the list->str
 * @h: points to first node
 *
 * Return: string arrays.
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t i = list_len(h), j;
	char **strs;
	char *str;

	if (!h || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints the elements of a linked list
 * @h: points to first node
 *
 * Return: s (size of list)
 */

size_t print_list(const list_t *h)
{
	size_t s = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		s++;
	}
	return (s);
}

/**
 * node_starts_with - return string of nodes with prefix.
 * @h: points to list head.
 * @prefix: string to match.
 * @c: the next character after prefix to match.
 *
 * Return: corresponding node or null
 */

list_t *node_starts_with(list_t *h, char *prefix, char c)
{
	char *p = NULL;

	while (h)
	{
		p = starts_with(h->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the node index.
 * @h: points to list head.
 * @node: pointer to the node.
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}

/**
 * print_list_str - prints the string element of a linked list.
 * @h: points to first node.
 *
 * Return: i (size of list)
 */

size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}
