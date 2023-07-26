#include "shell.h"
#include <sys/wait.h>

extern char **environ;

/**
 * main - Entry point for the simple shell program
 * Return: 0 on success, 1 on failure
 */

int main(void)
{
    char *prompt = "cisfun$ ";
    size_t n = 0;
    char *lineptr = NULL;
    ssize_t character_count;
    pid_t pid;
    int status;

    while (1)
    {
        char *token;
        char **argv;
        int i = 0;

        printf("%s", prompt);
        character_count = getline(&lineptr, &n, stdin);
        if (character_count == -1)
        {
            printf("exit\n");
            free(lineptr);
            exit(0);
        }

        lineptr[character_count - 1] = '\0';

        token = strtok(lineptr, " ");
        argv = malloc(sizeof(char *) * (character_count / 2 + 1));

        while (token != NULL)
        {
            argv[i] = strdup(token);
            token = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL;

        if (is_builtin(argv[0]))
        {
            execmd(argv);
            free_tokens(argv);
            free(lineptr);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("execvp");
            exit(1);
        }
        else
        {
            waitpid(pid, &status, 0);
        }

        free_tokens(argv);
        free(lineptr);
    }

    return 0;
}
