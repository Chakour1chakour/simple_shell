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
 * customSetEnv - Initialize a new environment variable
 *                                   or modify an existing one.
 * @c_info: Structure containing potential arguments.
 * Return: 0 on success, 1 on failure.
 */
int customSetEnv(info_t *c_info, char *name, char *value)
{
    if (c_info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (setenv(name, value, 1) == 0)
        return (0);
    return (1);
}

/**
 * customUnsetEnv - Remove an environment variable.
 * @c_info: Structure containing potential arguments.
 * Return: Always 0.
 */
int customUnsetEnv(info_t *c_info, char *name)
{
    int i;

    if (c_info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= c_info->argc; i++)
        unsetenv(name);

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
            return (p + strlen(name) + 1);
        node = node->next;
    }
    return (NULL);
}
