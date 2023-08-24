#include "shell.h"

/**
 * dup_char - to duplicate characters.
 * @beg: first index.
 * @end: last index.
 * @path_str: path string.
 *
 * Return: buf
 */

char *dup_char(char *path_str, int beg, int end)
{
	static char buf[1024];
	int i, j;
	i = 0;
	j = 0;

	for (j = 0, i = beg; i < end; i = i + 1)
	{
		if (path_str[i] != ':')
		{
			buf[j = j + 1] = path_str[i];
		}
	}
	buf[j] = 0;
	return (buf);
}

/**
 * exec_cmd - checks for executable commands.
 * @info: info struct.
 * @path: file path.
 *
 * Return: 1 (true), 0 (false)
 */

int exec_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;
	if (path == 0 || stat(path, &st))
		return 0;

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - checks for command in the path.
 * @path_str: path string.
 * @info: info struct.
 * @cmd: command to be checked for in path
 *
 * Return: cmd (full path) or NULL
 */

char *find_path(info_t *info, char *path_str, char *cmd)
{
	int n, initial;
	char *path;
	n = 0;
	initial = 0;

	if (path_str == 0)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (exec_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (path_str[n] == 0 || path_str[n] == ':')
		{
			path = dup_char(path_str, initial, n);
			if (*path == 0)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (exec_cmd(info, path))
				return (path);
			if (path_str[n] == 0)
				break;
			initial = n;
		}
		n++;
	}
	return (NULL);
}
	

