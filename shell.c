#include "shell.h"
#include <sys/wait.h>
#include <unistd.h>

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

        write(1, prompt, strlen(prompt));

        character_count = getline(&lineptr, &n, stdin);
        if (character_count == -1)
        {
            write(1, "exit\n", 5);
            free(lineptr);
            exit(0);
        }

        lineptr[character_count - 1] = '\0';  /*Remove the newline character */

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
                write(1, *env, strlen(*env));
                write(1, "\n", 1);
                env++;
            }
            continue;  /*Skip to the next iteration of the loop */
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
            /*Child process*/
            execvp(argv[0], argv);
            perror("execvp");
            exit(1);
        }
        else
        {
            /*Parent process */
            waitpid(pid, &status, 0);
        }

        free_tokens(argv);
        free(lineptr);
    }

    return (0);
}
