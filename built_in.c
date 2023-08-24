#include "shell.h"

/**
 * find_builtin - to find a builtin command.
 * @info: return and parameter info struct.
 *
 * Return: -1 if unable to find builtin command
 * 0 if success
 * 1 if fail
 * -2 if builtin signal exit()
 */

int find_builtin(info_t *info)
{
	int n, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintbl[n].type; n++)
		if (_strcmp(info->argv[0], builtintbl[n].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[n].func(info);
			break;
		}
	return (built_in_ret);
}
