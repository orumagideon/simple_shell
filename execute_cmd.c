#include "shell.h"

/**
 * execute - function forks child pid to exete command.
 * @fullPath: The full directory with command
 * @command: The user input
 * Return: status
 */
int execute(char *fullPath, char **command)
{
	pid_t child;
	int status = 0;
	struct stat st;

	child = fork();
	if (child == 0)
	{
		if (stat(fullPath, &st) == 0)
		{
			status = execve(fullPath, command, environ);
			exit(status);
		}
	}
	else
		wait(NULL);
	return (status);
}
