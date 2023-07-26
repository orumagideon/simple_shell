#include "shell.h"
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
}

int main(void)
{
    char *prompt = "#cisfun$ ";
    size_t n = 0;
    char *lineptr = NULL;
    ssize_t character_count;
    int status;
    pid_t pid;

    signal(SIGINT, handle_sigint);

    while (1)
    {
        char *token;
        char **argv;
        int i = 0;

        printf("%s", prompt);
        character_count = getline(&lineptr, &n, stdin);
        if (character_count == -1)
        {
            printf("\n");
            exit(0);
        }

        lineptr[character_count - 1] = '\0'; /* Remove the newline character */

        if (strcmp(lineptr, "exit") == 0)
        {
            free(lineptr);
            exit(0);
        }

        if (strcmp(lineptr, "env") == 0)
        {
            char **env = environ;
            while (*env)
            {
                printf("%s\n", *env);
                env++;
            }
            free(lineptr);
            continue; /* Skip to the next iteration of the loop */
        }

        token = strtok(lineptr, " ");
        argv = malloc(sizeof(char *) * (character_count / 2 + 1));

        while (token != NULL)
        {
            argv[i] = strdup(token);
            token = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL;

        pid = fork();

        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            /* Child process */
            execmd(argv);
            perror("execmd");
            exit(1);
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);
        }

        free_tokens(argv);
    }

    free(lineptr);
    return 0;
}
