#include "shell.h"
#include <stdlib.h>

extern char **environ;

void builtin_cd(char **argv)
{
    if (argv[1] != NULL)
    {
        if (chdir(argv[1]) != 0)
        {
            perror("cd");
        }
    }
}

void builtin_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
    }
}

int is_builtin(char *command)
{
    if (strcmp(command, "cd") == 0 || strcmp(command, "pwd") == 0 || strcmp(command, "exit") == 0 ||
        strcmp(command, "env") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void execmd(char **argv)
{
    char *command = NULL, *final_command = NULL;

    if (argv)
    {
        command = argv[0];

        if (is_builtin(command))
        {
            if (strcmp(command, "cd") == 0)
            {
                builtin_cd(argv);
            }
            else if (strcmp(command, "pwd") == 0)
            {
                builtin_pwd();
            }
            else if (strcmp(command, "exit") == 0)
            {
                free_tokens(argv);
                exit(0);
            }
            else if (strcmp(command, "env") == 0)
            {
                char **env = environ;
                while (*env)
                {
                    printf("%s\n", *env);
                    env++;
                }
            }
            else
            {
                /* Unknown built-in command */
                printf("Unknown command: %s\n", command);
            }
            return;
        }

        final_command = find_location(command);

        if (final_command != NULL && execve(final_command, argv, environ) == -1)
        {
            perror("Error");
        }
        else
        {
            printf("%s: command not found\n", command);
        }
    }
}
