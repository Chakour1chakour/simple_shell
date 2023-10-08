#include "shell.h"

/**
 * my_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **my_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @vari: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int my_unsetenv(info_t *info, char *vari)
{
    list_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !vari)
        return (0);

    while (node)
    {
        p = starts_with(node->str, vari);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * my_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @val: the string env var value
 * Return: Always 0
 */
int my_setenv(info_t *info, char *var, char *val)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !val)
        return (0);

    buf = malloc(_strlen(var) + _strlen(val) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var, NULL);
    _strcat(buf, "=", NULL);
    _strcat(buf, val, NULL);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            free(buf); // Free 'buf' since it's no longer needed
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf); // Free 'buf' since it's no longer needed
    info->env_changed = 1;
    return (0);
}
