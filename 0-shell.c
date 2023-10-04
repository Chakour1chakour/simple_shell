#include "shell.h"

/**
 * c_string_h - returns the length of a string
 * @str: the string to look up
 *
 * Return: integer length of the string
 */
int c_string_h(char *str)
{
    int h = 0;

    if (!str)
        return (0);

    while (*str++)
        h++;
    return (h);
} 
 
/**
 * c_string_cmp - performs comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int c_string_cmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    if (*str1 == *str2)
        return (0);
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * c_string_cat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: a pointer to the destination buffer
 */
char *c_string_cat(char *destination, const char *source)
{
    char *result = destination;

    while (*destination)
        destination++;
    while (*source)
        *destination++ = *source++;
    *destination = *source;
    return result;
} 

/**
 * c_starts_with - checks if a string starts with a specified substring.
 * @str: the string to search
 * @substring: the substring to find
 *
 * Return: a pointer to the next character in the string after the substring, or NULL if not found
 */
char *c_starts_with(const char *str, const char *substring)
{
    while (*substring)
    {
        if (*substring++ != *str++)
            return NULL;
    }
    return (char *)str;
}

