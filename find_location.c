#include "shell.h"

/**
 * main - Location finder.
 *
 * Return: Null
 */

char *find_location(char *command)
{
    char *path;
    struct stat buffer;

    if (command == NULL)
    {
        return NULL;
    }

    path = getenv("PATH");

    /* Check if it is a built-in command */
    if (is_builtin(command))
    {
        return NULL;
    }

    /* Check if it is an executable script in the current directory */
    if (stat(command, &buffer) == 0)
    {
        return strdup(command);
    }

    if (path != NULL)
    {
        char *path_replica = strdup(path);
        int length_command = strlen(command);
        char *path_tokens = strtok(path_replica, ":");

        while (path_tokens != NULL)
        {
            int length_directory = strlen(path_tokens);
            char *file_path = malloc(length_command + length_directory + 2);

            strcpy(file_path, path_tokens);
            strcat(file_path, "/");
            strcat(file_path, command);
            strcat(file_path, "\0");

            if (stat(file_path, &buffer) == 0)
            {
                free(path_replica);
                return file_path;
            }
            else
            {
                free(file_path);
                path_tokens = strtok(NULL, ":");
            }
        }
        free(path_replica);
    }

    return NULL;
}
