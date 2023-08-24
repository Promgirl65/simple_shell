#include "shell.h"

/**
 * get_history_file - to get file history.
 * @info: parameter struct.
 *
 * Return: his (history file)
 */

char *get_history_file(info_t *info)
{
	char *his, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	his = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!his)
		return (NULL);
	his[0] = 0;
	_strcpy(his dir);
	_strcat(his, "/");
	_strcat(his, HIST_FILE);
	return (his);
}

/**
 * write_history - creates new file or modify existing file.
 * @info: the parameter struct.
 *
 * Return: 1 success, -1 otherwise
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads file history.
 * @info: parameter struct.
 *
 * Return: histcount (success), 0 otherwise
 */

int read_history(info_t *info)
{
	int n, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (n = 0; n < fsize; n++)
		if (buf[n] == '\n')
		{
			buf[n] = 0;
			build_history_list(info, buf + last, linecount++);
			last = n + 1;
		}
	if (last != n)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds to list history.
 * @info: arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers list history after changes.
 * @info: arguments.
 *
 * Return: histcount (success)
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

/**
 * _myhistory - displays history list starting at 0.
 * @info: arguments.
 *
 *  Return: 0 (Always)
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
