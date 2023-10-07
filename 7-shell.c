#include "shell.h"
/**
* input_buf - buffers chained commands
* @par: parameter struct
* @bf: address of buffer
* @len: address of len var
**
Return: bytes read
*/
ssize_t input_bf(info_t *par, char **bf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;
if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)par->cmd_bf);*/
free(*bf);
*bf = NULL;
signal(SIGINT, sigHand);
#if USE_GETLINE
r = getln(bf, &len_p, stdin);
#else
r = getlne(par, bf, &len_p);
#endif
if (r > 0)
{
if ((*bf)[r - 1] == '\n')
{
(*bf)[r - 1] = '\0'; /* remove trailing newline */
r--;
} par->linecount_flag =
1;
r_comments(*bf);
build_history_list(par, *bf, par->histcount++);
/* if (_strchr(*bf, ';')) is this a command chain? */
{
*len = r;
par->cmd_bf = bf;
}
}
} return (
r);
}
/**
* getin - gets a line minus the newline
* @par: parameter struct
**
Return: bytes read
*/
ssize_t getin(info_t *par)
{
static char *bf; /* the ';' command chain buffer */
static size_t i, j, len;
ssize_t r = 0;
char **bf_p = &(par->arg), *p;
_putchar(BF_FLUSH);
r = input_bf(par, &bf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = bf + i; /* get pointer for return */
check_chain(par, bf, &j, i, len);
while (j < len) /* iterate to semicolon or end */
{
if (is_chain(par, bf, &j))
break;
j++;
}
i = j + 1; /* increment past nulled ';'' */
if (i >= len) /* reached end of buffer? */
{
i = len = 0; /* reset position and length */
par->cmd_bf_type = CMD_NORM;
}
*bf_p = p; /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}
*bf_p = bf; /* else not a chain, pass back buffer from _getline() */
return (r); /* return length of buffer from _getline() */
}
/**
* rebuf - reads a buffer
* @par: parameter struct
* @bf: buffer
* @i: size
**
Return: r
*/
ssize_t rebuf(info_t *par, char *bf, size_t *i)
{
ssize_t r = 0;
if (*i)
return (0);
r = read(par->readfd, bf, READ_BF_SIZE);
if (r >= 0)
*i = r;
return (r);
}
/**
* getln - gets the next line of input from STDIN
* @par: parameter struct
* @pnt: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
**
Return: s
*/
int getln(info_t *par, char **pnt, size_t *length)
{
static char bf[READ_BF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *pnt;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = rebuf(par, bf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = my_strchr(bf + i, '\n');
k = c ? 1 + (unsigned int)(c - bf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (s)
my_strncat(new_p, bf + i, k - i);
else
my_strncpy(new_p, bf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*pnt = p;
return (s);
}
/**
* sigHand - blocks ctrl-C
* @sinu: the signal number
**
Return: void
*/
void sigHand(__attribute__((unused))int sinu)
{
_puts("\n");
_puts("$ ");
_putchar(BF_FLUSH);
}
