#include "shell.h"
#include <sys/wait.h>

/**
 * main - Prompt user.
 *
 * Return: always 0
 */

extern char **environ;

int main(void)
{
    char *prompt = "cisfun$ "; // Prompt to be displayed
    size_t n = 0;
    char *lineptr = NULL; // Pointer to the user input line
    ssize_t character_count;
    pid_t pid;
    int status;

    while (1)
    {
        char *token;
        char **argv;
        int i = 0;

        printf("%s", prompt); // Display the prompt
        character_count = getline(&lineptr, &n, stdin); // Read user input from stdin
        if (character_count == -1)
        {
            printf("exit\n"); // If getline returns -1, it indicates an error or end of file
            free(lineptr);
            exit(0);
        }

        lineptr[character_count - 1] = '\0';  // Remove the newline character from the input

        if (strcmp(lineptr, "exit") == 0)
        {
            free(lineptr);
            exit(0); // Exit the shell if the user types "exit"
        }

        if (strcmp(lineptr, "env") == 0)
        {
            char **env = environ;
            while (*env)
            {
                printf("%s\n", *env); // Print the environment variables
                env++;
            }
            continue;  // Skip to the next iteration of the loop
        }

        token = strtok(lineptr, " "); // Tokenize the input line by spaces
        argv = malloc(sizeof(char *) * (character_count / 2 + 1));

        while (token != NULL)
        {
            argv[i] = strdup(token); // Create an argument vector
            token = strtok(NULL, " ");
            i++;
        }

        argv[i] = NULL; // Set the last element of the argument vector to NULL

        pid = fork();

        if (pid == -1)
        {
            perror("fork"); // Check for fork errors
            exit(1);
        }
        else if (pid == 0)
        {
            /* Child process */
            execvp(argv[0], argv); // Execute the command entered by the user
            perror("execvp"); // If execvp returns, it indicates an error
            exit(1);
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0); // Wait for the child process to complete
        }

        free_tokens(argv); // Free the memory allocated for the argument vector
        free(lineptr); // Free the memory allocated for the input line
    }

    return 0;
}

