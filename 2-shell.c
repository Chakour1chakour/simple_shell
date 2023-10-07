#include "shell.h"

/**
 * his - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @infarg: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int his(info_t *infarg)
{
    print_list(infarg->his);
    return (0);
}

/**
 * unsetal - sets alias to string
 * @par: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unsetal(info_t *par, char *str)
{
    char *p, c;
    int ret;
    p = strchr(str, '='); /* Change _strchr to strchr */
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_nd_at_index(&(par->alias),
                             get_nd_index(par->alias, nd_starts_with(par->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * setal - sets alias to a string
 * @par: parameter struct
 * @str: string alias
 * Return: Always 0 on success, 1 on error
 */
int setal(info_t *par, char *str)
{
    char *p;
    p = strchr(str, '='); /* Change _strchr to strchr */
    if (!p)
        return (1);
    if (!*++p)
        return (unsetal(par, str));
    unsetal(par, str);
    return (add_nd_end(&(par->alias), str, 0) == NULL);
}

/**
 * pal - prints an alias string
 * @nd: the alias node
 * Return: Always 0 on success, 1 on error
 */
int pal(list_t *nd)
{
    char *p = NULL, *a = NULL;
    if (nd)
    {
        p = strchr(nd->str, '='); /* Change _strchr to strchr */
        for (a = nd->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * mal - mimics the alias builtin
 * @infarg: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int mal(info_t *infarg)
{
    int i = 0;
    char *p = NULL;
    list_t *nd = NULL;
    if (infarg->argc == 1)
    {
        nd = infarg->alias;
        while (nd)
        {
            pal(nd);
            nd = nd->next;
        }
        return (0);
    }
    for (i = 1; infarg->argv[i]; i++)
    {
        p = strchr(infarg->argv[i], '='); /* Change _strchr to strchr */
        if (p)
            setal(infarg, infarg->argv[i]);
        else
            pal(nd_starts_with(infarg->alias, infarg->argv[i], '='));
    }
    return (0);
}

