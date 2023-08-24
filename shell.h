#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/* read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* num_alpha conversion */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* using system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/*using environ*/
extern char **environ;

/**
<<<<<<< HEAD
* struct liststr - linked list string.
* @num: number of strings.
* @str: the string.
* @next: pointer to the next node.
*/
=======
<<<<<<< HEAD
 * struct passinfo - groups the variables under struct.
=======
 * struct liststr - string of singly linked list.
 * @num: number of strings.
 * @str: a string.
 * @next: pointer to the next node.
 */
>>>>>>> 652e9d5737ed8080af5c78a799c041bb7d65cc0b

typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
<<<<<<< HEAD
* struct passinfo - groups pseudo-arguements passed to function.
* @arg: generated strings of arguements from getline.
* @argv: array generated from arg.
* @path: current command string path.
* @argc: argument count.
* @line_count: counts error lines.
* @err_num: error code for exit()s.
* @linecount_flag: flag to control line count.
* @fname: program filename.
* @env: local copy of environ linked list.
* @environ: modifies a copy of environ from LL env.
* @history: history node.
* @alias: alias node.
* @env_changed: is on if environ changed.
* @status: return status of last executed command.
* @cmd_buf: address of pointer to cmd_buf and is on if chaining.
* @cmd_buf_type: CMD_type ||, &&, ;
* @readfd: the fd from which to read line input.
* @histcount: history line num count.
*/

typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
=======
 * struct passinfo - groups the variables of different data types together
 * under struct.
>>>>>>> 5eae8445a28900da613d4a72db40f883b5ae5664
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
<<<<<<< HEAD
	int argc, status, env_changed, err_num;
	int linecount_flag, readfd, histcount, cmd_buf_type;
	char *fname, *arg, *path;
	char **argv, **environ, **cmd_buf;
=======
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
>>>>>>> 5eae8445a28900da613d4a72db40f883b5ae5664
	unsigned int line_count;
	list_t *env;
	list_t *history;
	list_t *alias;
>>>>>>> 652e9d5737ed8080af5c78a799c041bb7d65cc0b
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
* struct builtin - contains builtin strings and related functions.
* @type: builtin command flag.
* @func: function.
*/

typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string_1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors_1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
