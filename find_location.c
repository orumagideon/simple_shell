#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * _myexit - exits the shell
 * @info: the structure containing arguments
 *
 * Return: 0 if successful, 1 otherwise
 */
int _myexit(info_t *info)
{
    if (info->argc == 1)
        exit(0);

    if (atoi(info->argv[1]) < 0)
    {
        perror("Invalid exit value");
        return (1);
    }
    exit(atoi(info->argv[1]));
}

/**
 * _myenv - prints the current environment
 * @info: the structure containing arguments
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
    int i;

    for (i = 0; info->env[i]; i++)
    {
        write(STDOUT_FILENO, info->env[i], strlen(info->env[i]));
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}
