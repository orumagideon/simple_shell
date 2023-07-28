#include "shell.h"
/**
 * env - Prints env
 * @env: printed environment.
 * Return: void
 */
void env(char **env)
{
	int i = 0;

	while (env[i])
	{
		write(1, env[i], _strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}
