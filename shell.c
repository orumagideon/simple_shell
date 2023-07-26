#include "shell.h"

/**
 * main - main shell loop
 * @argc: argument count
 * @argv: argument vector
 * @env: environment variables
 * Return: exit status
 */
int main(int argc, char *argv[], char **env)
{
    info_t info = {NULL, NULL, NULL, 0, 0, 0, 0};

    init_info(&info, env);
    info.argv = argv;
    info.argc = argc;

    while (1)
    {
        if (interactive(&info))
            display_prompt(1);
        if (get_line(&info) == -1)
            break;
        parse_line(&info);
        execute_line(&info);
        free_info(&info);
    }
    return (info.status);
}
