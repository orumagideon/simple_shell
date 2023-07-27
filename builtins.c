#include "shell.h"

/**
 * exit_sh - exits from shell
 * @command: The command input
 * Return: 0 for success
 */
int exit_sh(char **command)
{
	if (*command)
	{
		buffers1(NULL, NULL);
		buffers2(NULL, NULL);
		buffers3(NULL, NULL);
		buffers4(NULL, NULL);
		buffers5(NULL);
		exit(2);
	}
	return (0);
}

/**
 * cd - Change directory function
 * @command: The input command
 * Return: 0 for success
 */
int cd(char **command)
{
	chdir(command[1]);
	return (0);
}

/**
 * printenv - The print env function
 * @command: Command pointer
 * Return: 0 for success
 */
int printenv(char **command)
{
	int i;

	if (*command)
	{
		i = 0;
		while (environ[i])
		{
			write(1, environ[i], _strlen(environ[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}

/**
 * checkBuiltins - Call function
 * @combine: complete directory
 * @command: input command
 * Return: Process from directory
 */
int checkBuiltins(char *combine, char **command)
{
	int i;
	char *array[] = {"exit", "cd", "env", NULL};

	typedef int (*Builtins)(char **);
	Builtins functions[] = {&exit_sh, &cd, &printenv};

	i = 0;
	while (array[i] != NULL)
	{
		if (_strcmp(array[i], command[0]) == 0)
			return (functions[i](command));
		i++;
	}
	return (execute(combine, command));
}
