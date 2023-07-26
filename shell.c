#include "shell.h"
#include <sys/wait.h>

extern char **environ;

ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
    static char buffer[4096];
    static char *bufptr = buffer;
    static size_t nleft = 0;
    ssize_t nread;
    
    char *newline;

    if (nleft == 0) {
        nread = read(fileno(stream), buffer, sizeof(buffer));
        if (nread <= 0) {
            return nread;
        }
        bufptr = buffer;
        nleft = nread;
    }

    *lineptr = bufptr;

    newline = memchr(bufptr, '\n', nleft);
    if (newline) {
        *newline = '\0';
        nread = newline - bufptr + 1;
    } else {
        nread = nleft;
    }

    bufptr += nread;
    nleft -= nread;

    if (n) {
        *n = nread;
    }

    return nread;
}

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
        character_count = _getline(&lineptr, &n, stdin);
        if (character_count == -1)
        {
            printf("exit\n");
            exit(0);
        }

        lineptr[character_count - 1] = '\0';  /*Remove the newline character */

        token = strtok(lineptr, " ");
        argv = malloc(sizeof(char *) * (character_count / 2 + 1));

        while (token != NULL)
        {
            argv[i] = strdup(token);
            token = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL;

        if (argv[0] != NULL) {
            pid = fork();

            if (pid == -1)
            {
                perror("fork");
                exit(1);
            }
            else if (pid == 0)
            {
                /*Child process*/
                execmd(argv);
                perror("execvp");
                exit(1);
            }
            else
            {
                /*Parent process */
                waitpid(pid, &status, 0);
            }
        }

        free_tokens(argv);
    }

    return 0;
}
