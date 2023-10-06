#include "shell.h"

/**
 * my_strncpy - copies a string with a maximum length
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the maximum number of characters to be copied
 * Return: a pointer to the destination string
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    char *result = dest;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return result;
}

/**
 * my_strncat - concatenates two strings with a maximum length
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of bytes to be used
 * Return: a pointer to the destination string
 */
char *my_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';

    return dest;
}

/**
 * my_strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the first occurrence of the character, or NULL if not found
 */
char *my_strchr(const char *s, int c)
{
    while (*s != '\0') {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}
