#include "shell.h"

/**
 **strncpy - copies a string
 *@d: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *strncpy(char *d, char *src, int n)
{
	int i, j;
	char *s = d;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		d[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strncat - concatenates two strings
 *@d: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *d, char *src, int n)
{
	int i, j;
	char *s = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		d[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		d[i] = '\0';
	return (s);
}

/**
 **strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

