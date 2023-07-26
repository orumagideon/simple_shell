#include "shell.h"

void free_tokens(char **tokens) {
    char **current_token = tokens;
    while (*current_token) {
        free(*current_token);
        ++current_token;
    }
    free(tokens);
}

extern char **environ;

int is_builtin(char *command)
{
    if (strcmp(command, "cd") == 0 || strcmp(command, "pwd") == 0 || strcmp(command, "exit") == 0 ||
        strcmp(command, "env") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void execmd(char **argv)
{
    char *command = NULL, *final_command = NULL;

    if (argv) {
        command = argv[0];

        if (is_builtin(command)) {
            if (strcmp(command, "cd") == 0) {
                /*Handle cd command */
                if (argv[1] != NULL) {
                    if (chdir(argv[1]) != 0) {
                        perror("cd");
                    }
                }
            } else if (strcmp(command, "pwd") == 0) {
                /*Handle pwd command */
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("%s\n", cwd);
                } else {
                    perror("pwd");
                }
            } else if (strcmp(command, "exit") == 0) {
                /*Handle exit command */
                int status = 0;
                if (argv[1] != NULL) {
                    status = atoi(argv[1]);
                }
                free_tokens(argv);
                exit(status);
            } else if (strcmp(command, "env") == 0) {
                /*Handle env command */
                char **env = environ;
                while (*env) {
                    printf("%s\n", *env);
                    env++;
                }
            } else {
                /*Unknown built-in command */
                printf("Unknown command: %s\n", command);
            }
            return;
        }

        final_command = find_location(command);

        if (final_command != NULL && execve(final_command, argv, environ) == -1) {
            perror("Error:");
        }
    }
}
