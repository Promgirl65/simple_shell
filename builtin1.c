#include "shell.h"

/**
* _myhistory - displays history list one command per line preceded
* with line numbers, starting at 0.
* @info: structure containing arguments.
*
* Return: Always 0
*/

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
* unset_alias - set alias to strings.
* @info: parameter struct.
* @str: string alias.
*
* Return: Always 0 on success, 1 on error
*/

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;
	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
* set_alias - set alias to strings.
* @info: parameter struct.
* @str: string alias.
*
* Return: Always 0 on success, 1 on error
*/

int set_alias(info_t *info, char *str)
{
	char *p;
	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
* print_alias - prints alias string.
* @node: alias node
*
* Return: Always 0 on success, 1 on error
*/

int print_alias(list_t *node)
{
	char *c = NULL, *s = NULL;
	if (node)
	{
		c = _strchr(node->str, '=');
		for (s = node->str; s <= c; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
* _myalias - mimics builtin man.
* @info: structure containing arguments.
*
* Return: Always 0
*/

int _myalias(info_t *info)
{
	int n = 0;
	char *a = NULL;
	list_t *node = NULL;
	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; info->argv[n]; n++)
	{
		a = _strchr(info->argv[n], '=');
		if (a)
			set_alias(info, info->argv[n]);
		else
			print_alias(node_starts_with(info->alias, info->argv[n], '='));
	}
	return (0);
}
