#include "shell.h"

/**
* _myenv - prints current environment.
* @info: structure containing arguments.
*
* Return: Always 0
*/

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
* _getenv - gets the value of environ variable.
* @info: structure containing arguments.
* @name: env var name.
*
* Return: the value
*/

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;
	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
* _mysetenv - Initialize new environment variable.
* @info: structure containing arguments.
*
* Return: Always 0
*/

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
* _myunsetenv - removes an environment variable.
* @info: structure containing arguments.
*
* Return: Always 0
*/

int _myunsetenv(info_t *info)
{
	int i;
	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}

/**
* populate_env_list - populates the env linked list.
* @info: structure containing arguments.
*
* Return: Always 0
*/

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;
	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
