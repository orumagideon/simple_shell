#include "shell.h"
#include <sys/wait.h>

extern char **environ;

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
        char *command;
        char *final_command;

        printf("%s", prompt);
        character_count = getline(&lineptr, &n, stdin);
        if (character_count == -1)
        {
            printf("exit\n");
            free(lineptr);
            exit(0);
        }

        lineptr[character_count - 1] = '\0';  /* Remove the newline character */

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
            continue;  /* Skip to the next iteration of the loop */
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

        command = argv[0];
        if (command == NULL)
        {
            free_tokens(argv);
            continue;
        }

        final_command = find_location(command);
        if (final_command == NULL)
        {
            printf("Command not found: %s\n", command);
            free_tokens(argv);
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
            /* Child process */
            execve(final_command, argv, environ);
            perror("execve");
            exit(1);
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);
        }

        free_tokens(argv);
        free(lineptr);
    }

    return 0;
}
