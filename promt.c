#include "shell.h"
/**
 * prompt - prints the prompt
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "$ ", 2);
}
