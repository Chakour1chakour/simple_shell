#include "shell.h"

/**
 * c_print_environment - prints the current environment
 * @c_info: Structure containing potential arguments.
 * Return: Always 0
 */
int c_print_environment(info_t *c_info)
{
    print_list_str(c_info->environment);
    return (0);
}

/**
 * c_set_environment_variable - Initialize a new environment variable
 *                                   or modify an existing one.
 * @c_info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure.
 */
int c_set_environment_variable(info_t *c_info)
{
    if (c_info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (custom_setenv(c_info, c_info->argv[1], c_info->argv[2]) == 0)
        return (0);
    return (1);

/**
 * c_unset_environment_variable - Remove an environment variable.
 * @c_info: Structure containing potential arguments.
 * Return: Always 0.
 */
int c_unset_environment_variable(info_t *c_info)
{
    int i;

    if (c_info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= c_info->argc; i++)
        custom_unsetenv(c_info, c_info->argv[i]);

    return (0);
}

/**
 * p_environment_list - Populates the environment linked list.
 * @c_info: Structure containing potential arguments.
 * Return: Always 0.
 */
int p_environment_list(info_t *c_info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    c_info->environment = node;
    return (0);
}

/**
 * c_get_environment_variable - gets the value of an environment variable
 * @c_info: Structure containing potential arguments.
 * @name: Environment variable name.
 * Return: The value of the variable or NULL if not found.
 */
char *c_get_environment_variable(info_t *c_info, const char *name)
{
    list_t *node = c_info->environment;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}
