#include "shell.h"

/**
 * _setenv - create or initialize a new environment var.
 * @env_var: environment variable.
 * @num: value of the environment variable.
 * @info: arguments.
 *
 * Return: 0 (Always)
 */

int _setenv(info_t *info, char *env_var, char *num)
{
	char *c;
	char *buffer = NULL;
	list_t *node;

	if (env_var == 0 || num == 0)
	{
		return (0);
	}
	buffer = malloc(_strlen(env_var) + _strlen(num) + 2);
	if (buffer == 0)
	{
		return (1);
	}
	_strcpy(buffer, env_var);
	_strcat(buffer, "=");
	_strcat(buffer, num);
	node = info->env;
	while (node)
	{
		c = starts_with(node->str, env_var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - delete/unset environment var.
 * @env_var: environment variable.
 * @info: arguments.
 *
 * Return: 1(success), 0(fail)
 */

int _unsetenv(info_t *info, char *env_var)
{
	char *c;
	list_t *node = info->env;
	size_t s = 0;

	if (node == 0 || env_var == 0)
	{
		return (0);
	}
	while (node)
	{
		c = starts_with(node->str, env_var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), s);
			s = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		s = s + 1;
	}
	return (info->env_changed);
}

/**
 * _mysetenv - creates or initialize a new environment var.
 * @info: arguments.
 *
 * Return: 0 (Always)
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myenv - to print working environment.
 * @info: arguments.
 *
 * Return: 0 (Always)
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_environ - to return working environment.
 * @info: arguments.
 *
 * Return: 0 (Always)
 */

char **get_environ(info_t *info)
{
	if (info->environ == 0 || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _getenv - to get the value of environment var.
 * @id: environment variable.
 * @info: arguments.
 *
 * Return: 0(Always)
 */

char *_getenv(info_t *info, const char *id)
{
	char *c;
	list_t *node = info->env;

	while (node)
	{
		c = starts_with(node->str, id);
		if (c && *c)
		{
			return (c);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - to populate environment list.
 * @info: arguments.
 *
 * Return: 0 (Always)
 */

int populate_env_list(info_t *info)
{
	size_t s;
	list_t *node = NULL;

	for (s = 0; environ[s]; s = s + 1)
	{
		add_node_end(&node, environ[s], 0);
	}
	info->env = node;
	return (0);
}

/**
 * _myunsetenv - removes or deletes environment variable.
 * @info; arguments.
 *
 * Return: 0 (Always)
 */

int _myunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
	{
		_unsetenv(info, info->argv[n]);
	}
	return (0);
}
