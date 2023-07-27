#include "shell.h"
/**
 * prompt - Prints prompt
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "$ ", 2);
}
