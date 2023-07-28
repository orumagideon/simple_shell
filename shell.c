#include "shell.h"
/**
 * main - The main function
 * @argc: The number of arg
 * @argv: arg
 * @envp: The program’s environ
 * Return: 0 for sucess
 */
int main(int argc, char **argv, char **envp)
{
	if (argc == 1 || argv[1] == NULL)
	loop(envp);

	return (0);
}
