#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BF_SIZE 1024
#define WRITE_BF_SIZE 1024
#define BF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for the function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on, count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
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
    list_t *his;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_bf; /* pointer to cmd ; chain buffer, for memory management */
    int cmd_bf_type; /* CMD_type ||, &&, ; */
    int readfd;
    int histcount;
    int err_atoi;
    list_t *environment; /* Added environment member */
} info_t;

#define INFO_INIT \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
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

/* 4-shell.c.c */
void _puts(char *);
int _putchar(char);
int _putf(char c, int fd);
int _putsf(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *, size_t*);

/* toem_string1.c */
char *_strcpy(char *, char *, size_t*);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* 6-shell.c */
char *my_strncpy(char *, const char *, size_t);
char *my_strncat(char *, const char *, size_t);
char *my_strchr(const char *, int);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* 0-shell.c */
int wakeup(info_t *);
int dilemma(char, char *);
int is_giga(int);
int conin(char *);

/* 5-shell.c */
int dalemma(char *);
void p_error(info_t *, char *);
int print(int, int);
char *c_number(long int, int, int);
void r_comments(char *);

/* 1-shell.c */
int _cexit(info_t *);
int _cd(info_t *);
int _wakeup(info_t *);

/* 2-shell.c */
int his(info_t *);
int mal(info_t *);

/*7-shell.c */
ssize_t getin(info_t *);
int getlne(info_t *, char **, size_t *);
void sigHand(int);

/* info */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* 3-shell.c */
int env(info_t *);
char *genv(info_t *, const char *);
int p_env_list(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
/* getenv.c code */
char **get_environ(info_t *);
/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_nd(list_t **, const char *, int);
list_t *add_nd_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_nd_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *nd_starts_with(list_t *, char *, char);
ssize_t get_nd_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* Function Declarations Added */
void print_error(info_t *info, char *estr);
char *_getenv(info_t *info, char *name);
void _puts(char *str);
int _putchar(char c);
void _eputs(char *str);
int _eputchar(char c);
void _custom_setenv(info_t *info, char *name, char *value);
int populate_env_list(info_t *);
int err_atoi(char *);
/* print_d */
/**
 * print_d - prints an integer to a file descriptor
 * @input: the integer to be printed
 * @fde: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fde);

#endif

