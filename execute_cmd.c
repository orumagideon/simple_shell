#include "shell.h"
#include <string.h>

/**
 * interactive - returns 1 if shell is in interactive mode
 * @info: the structure address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * display_prompt - display the shell prompt
 * @newline: boolean to include newline character
 */
void display_prompt(int newline)
{
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "$ ", 2);
}

/**
 * get_line - read a line from stdin
 * @info: the structure address
 *
 * Return: length of the line on success, -1 on end of file or error
 */
int get_line(info_t *info)
{
    ssize_t len = 0;
    size_t buf_size = 0;

    len = getline(&(info->line), &buf_size, stdin);
    if (len == -1)
        return (-1);

    info->line[len - 1] = '\0';
    return (len);
}

/**
 * parse_line - parse the line into arguments
 * @info: the structure address
 */
void parse_line(info_t *info)
{
    char *token;
    int i = 0;

    info->argv = malloc(sizeof(char *) * 2);
    token = strtok(info->line, " ");
    while (token)
    {
        info->argv[i++] = token;
        token = strtok(NULL, " ");
        info->argv = realloc(info->argv, sizeof(char *) * (i + 1));
    }
    info->argv[i] = NULL;
    info->argc = i;
}

/**
 * execute_line - execute the command in the line
 * @info: the structure address
 */
void execute_line(info_t *info)
{
    pid_t pid;
    int status;

    if (strcmp(info->argv[0], "exit") == 0)
    {
        _myexit(info);
        exit(0);
    }
    else if (strcmp(info->argv[0], "env") == 0)
    {
        _myenv(info);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(info->argv[0], info->argv, info->env) == -1)
            perror("Error");
        exit(1);
    }
    else
        wait(&status);
}

/**
 * init_info - initialize the info structure
 * @info: the structure address
 * @env: environment variables
 */
void init_info(info_t *info, char **env)
{
    info->env = env;
    info->line = NULL;
    info->argv = NULL;
    info->readfd = STDIN_FILENO;
}

/**
 * free_info - free info structure members
 * @info: the structure address
 */
void free_info(info_t *info)
{
    free(info->line);
    info->line = NULL;
    free(info->argv);
    info->argv = NULL;
}
