#include "shell.h"

/**
 * c_exit - exits the shell
 * @c_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if c_info->argv[0] != "exit"
 */
int c_exit(info_t *c_info)
{
    int exit_check;

    if (c_info->argv[1]) /* If there is an exit argument */
    {
        exit_check = err_atoi(c_info->argv[1]);
        if (exit_check == -1)
        {
            c_info->status = 2;
            print_error(c_info, "Illegal number: ");
            e_puts(c_info->argv[1]);
            e_putchar('\n');
            return (1);
        }
        c_info->err_num = err_atoi(c_info->argv[1]);
        return (-2);
    }
    c_info->err_num = -1;
    return (-2);
}

/**
 * c_help - changes the current directory of the process
 * @c_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int c_help(info_t *c_info)
{
	char **arg_array;

	arg_array = c_info->argv;
	e_puts("help call works. Function not yet implemented \n");
	if (0)
		e_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * c_change_directory - changes the current directory of the process
 * @c_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int c_change_directory(info_t *c_info)
{
    char *current_path, *new_path, buffer[1024];
    int change_dir_status;

    current_path = getcwd(buffer, 1024);
    if (!current_path)
        e_puts("TODO: >>getcwd failure emsg here<<\n");
    if (!c_info->argv[1])
    {
        new_path = getenv(c_info, "HOME=");
        if (!new_path)
            change_dir_status = chdir((new_path = getenv(c_info, "PWD=")) ? new_path : "/");
        else
            change_dir_status = chdir(new_path);
    }
    else if (strcmp(c_info->argv[1], "-") == 0)
    {
        if (!getenv(c_info, "OLDPWD="))
        {
            e_puts(current_path);
            e_putchar('\n');
            return (1);
        }
        e_puts(getenv(c_info, "OLDPWD="));
        e_putchar('\n');
        change_dir_status = chdir((new_path = getenv(c_info, "OLDPWD=")) ? new_path : "/");
    }
    else
        change_dir_status = chdir(c_info->argv[1]);
    if (change_dir_status == -1)
    {
        print_error(c_info, "can't cd to ");
        e_puts(c_info->argv[1]);
        e_putchar('\n');
    }
    else
    {
        setenv(c_info, "OLDPWD", getenv(c_info, "PWD="));
        setenv(c_info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}
