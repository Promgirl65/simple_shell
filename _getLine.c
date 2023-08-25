#include "shell.h"
/**
* input_buf -buffers the chain commands.
* @info:The parameter struct.
* @buf:The address of buffer.
* @len:the address of len var.
*
* Return:read bytes.
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
if (!*len) /* if there is nothing  in the buffer, fill it */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);

#if USE_GETLINE

r = getline(buf, &len_p, stdin);

#else

r = _getline(info, buf, &len_p);

#endif

if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /*its removes trailing newline */
r--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */

{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}
/**
* get_input -its gets a line minus the newline.
* @info:the parameter struct.
*
* Return:read bytes.
*/
ssize_t get_input(info_t *info)
{
static char *buf; /* the ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(info->arg), *p;
_putchar(BUF_FLUSH);
r = input_buf(info, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* there is commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = buf + i; /*the get pointer for return */
check_chain(info, buf, &j, i, len);
while (j < len) /*its iterate to semicolon or end */
{
if (is_chain(info, buf, &j))
break;
j++;
}
i = j + 1; /*the increment past nulled ';'' */
if (i >= len) /*its reaches end of buffer? */
{
i = len = 0; /*its reset position and length */
info->cmd_buf_type = CMD_NORM;
}
*buf_p = p; /*its pass back pointer to current command position */
return (_strlen(p)); /*its return length of current command */

}
*buf_p = buf; /* else not a chain,its pass back buffer from _getline() */
return (r); /*its return length of buffer from _getline() */
}
/**
* read_buf -its reads a buffer.
* @info:the parameter struct
* @buf:the buffer
* @i:the size
*
* Return: r
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t r = 0;
if (*i)
return (0);
r = read(info->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}
/**
* _getline -its get the next line of input from STDIN.
* @info:the parameter struct.
* @ptr:the address of the pointer to buffer, preallocated or NULL.
* @length:the size of preallocated ptr buffer if not NULL.
*
* Return: u
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t a = 0, u = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
u = *length;
if (i == len)
i = len = 0;

a = read_buf(info, buf, &len);
if (a == -1 || (a == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, u, u ? u + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (u)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);
u += k - i;
i = k;
p = new_p;
if (length)
*length = u;
*ptr = p;
return (u);
}

/**
* sigintHandler -its blocks ctrl-C
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
