#include "shell.h"

/**
 * sigintHandler - interrupt and terminate ctrl + C.
 * @sig_num: signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}

/**
 * input_buf - buffer command chain before execution.
 * @info: struct for parameter.
 * @buf: buffer address.
 * @len: address of len.
 *
 * Return: size
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t size = 0;
	size_t len_r = 0;

	if (!*len)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		size = getline(buf, &len_r, stdin);
#else
		size = _getline(info, buf, &len_r);
#endif
		if (size > 0)
		{
			if ((*buf)[size - 1] == '\n')
			{
				(*buf)[size - 1] = '\0';
				size--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{			{
				*len = size;
				info->cmd_buf = buf;
			}
		}
	}
	return (size);
}

/**
 * get_input - to get a line -  newline.
 * @info: parameter struct
 *
 * Return: size
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, n, len;
	ssize_t size = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	size = input_buf(info, &buf, &len);
	if (size == -1) /* EOF */
		return (-1);
	if (len)
	{
		n = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &n, i, len);
		while (n < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &n))
				break;
			n = n + 1;
		}

		i = n + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (size); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads buffer.
 * @info: parameter struct.
 * @buf: a buffer
 * @s: size
 *
 * Return: i
 */
ssize_t read_buf(info_t *info, char *buf, size_t *s)
{
	ssize_t i = 0;

	if (*s)
		return (0);
	i = read(info->readfd, buf, READ_BUF_SIZE);
	if (i >= 0)
		*s = i;
	return (i);
}

/**
 * _getline - gets next input line from std input.
 * @info: parameter struct.
 * @ptr: pointer address to buffer.
 * @len: the size of preallocated ptr buffer.
 *
 * Return: t
 */

int _getline(info_t *info, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, n;
	size_t k;
	ssize_t r = 0, t = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len)
		t = *len;
	if (i == n)
		i = n = 0;

	r = read_buf(info, buf, &n);
	if (r == -1 || (r == 0 && n == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : n;
	new_p = _realloc(p, t, t ? t + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (t)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	t += k - i;
	i = k;
	p = new_p;

	if (len)
		*len = t;
	*ptr = p;
	return (t);
}
