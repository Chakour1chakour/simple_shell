#include "shell.h"
/**
* _puts - prints an input string
* @str: the string to be printed
**
Return: Nothing
*/
void _puts(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}
/**
* _putchar - writes the character c to stderr
* @ch: character to print
Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char ch)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
} if (
ch
!= BUF_FLUSH)
buf[i++] = ch;
return (1);
}
/**
* _putf - writes the character c to given fd
* @ch: The character to print
* @fd: The filedescriptor to write to
Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putf(char ch, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
} if (
ch
!= BUF_FLUSH)
buf[i++] = ch;
return (1);
}
/**
* _putsf - prints an input string
* @str: the string to be printed
* @fd: the filedescriptor to write to
**
Return: the number of chars put
*/
int _putsf(char *str, int fd)
{
int i = 0;
if (!str)
return (0);
while (*str)
{
i += _putf(*str++, fd);
} return (
i);
}
