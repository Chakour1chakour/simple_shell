#include "shell.h"
/**
* wakeup - returns true if shell is in wakeup mode
* @wakein: struct address
**
Return: 1 if wakeup mode, 0 otherwise
*/
int wakeup(info_t *wakein)
{
return (isatty(STDIN_FILENO) && wakein->readfd <= 2);
}
/**
* dilemma - checks if character is a delimeter
* @h: the char to check
* @limde: the delimeter string
* Return: 1 if true, 0 if false
*/
int dilemma(char h, char *limde)
{
while (*limde)
if (*limde++ == h)
return (1);
return (0);
}
/**
* is_giga - checks for alphabetic character
* @h: The character to input
* Return: 1 if h is alphabetic, 0 otherwise
*/
int is_giga(int h)
{
if ((h >= 'a' && h <= 'z') || (h >= 'A' && h <= 'Z'))
return (1);
else
return (0);
}
/**
* _conin - converts a string to an integer
* @c: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int _conin(char *c)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;
for (i = 0; c[i] != '\0' && flag != 2; i++)
{
if (c[i] == '-')
sign *= -1;
if (c[i] >= '0' && c[i] <= '9')
{
flag = 1;
result *= 10;
result += (c[i] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -result;
else
output = result;
return (output);
}
