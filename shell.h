#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

/* the buffers for read and write */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* to convert */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* using getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* the CMD chain */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - string of singly linked list.
 * @num: number of strings.
 * @str: a string.
 * @next: pointer to the next node.
 */

typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct passinfo - groups the variables of different data types together
 * under struct.
 * @fname: file name.
 * @argc: counts arguments.
 * @argv: argument vector.
 * @arg: generated string of arguments.
 * @line_count: counts error lines.
 * @linecount_flag: flag to control line count.
 * @alias: alias or alternate node.
 * @env: environment variables.
 * @env_changed: to track changing environment variables.
 * @environ: to modify environment variable.
 * @readfd: to read from file descriptor.
 * @cmd_buf: pointer address.
 * @cmd_buf_type: command type.
 * @history: creates history.
 * @histcount: to count history list.
 * @err_num: error code.
 * @path: command path.
 * @status: status of the command executed.
 */

typedef struct passinfo
{
	int argc;
	int status;
	int env_changed;
	int err_num;
	int linecount_flag;
	int readfd;
	int histcount;
	int cmd_buf_type;
	char *fname;
	char *arg;
	char *path;
	char **argv;
	char **environ;
	char **cmd_buf;
	unsigned int line_count;
	list_t *env;
	list_t *history;
	list_t *alias;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

/**
 * struct builtin - string for builtin
 * @func: builtin function
 * @type: builtin type
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
}
builtin_table;

void _puts(char *);
void _eputs(char *);
void sigintHandler(int);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
void print_error(info_t *, char *);
void set_info(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);
void remove_comments(char *);
void clear_info(info_t *);
void free_str(char **);
void free_info(info_t *, int);
void *_realloc(void *, unsigned int, unsigned int);
char *_strcpy(char *, char *);
char *_strncpy(char *, char *, int);
char *_strcat(char *, char *);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strdup(const char *);
char *dup_char(char *, int, int);
char *starts_with(const char *, const char *);
char *find_path(info_t *, char *, char *);
char **get_environ(info_t *);
char *_getenv(info_t *, const char *);
char *get_history_file(info_t *info);
char **strtow1(char *, char *);
char **strtow2(char *, char);
char *convert_number(long int, int, int);
char *_memset(char *, char, unsigned int);
int _putchar(char);
int _strlen(char *);
int replace_string(char **, char *);
int _strcmp(char *, char *);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char);
int is_chain(info_t *, char *, size_t *);
int exec_cmd(info_t *, char *);
int hsh(info_t *, char **);
int loophsh(char **);
int find_builtin(info_t *);
int write_history(info_t *info);
int read_history(info_t *info);
int print_d(int, int);
int _myhistory(info_t *);
int _myalias(info_t *);
int replace_alias(info_t *);
int replace_vars(info_t *);
int _mycd(info_t *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int bfree(void **);
int _isalpha(int);
int is_delim(char, char *);
int interactive(info_t *);
int _atoi(char *);
int _getline(info_t *, char **, size_t *);
int erratoi(char *);
int populate_env_list(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);
ssize_t get_input(info_t *);
void free_list(list_t **);
list_t *node_starts_with(list_t *, char *, char);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
char **list_to_strings(list_t *);

#endif
