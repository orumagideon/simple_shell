#include "shell.h"
/**
 * handler - Function determines signal
 * @sig: the signal
 * Return: void
 */
void  handler(int sig)
{
	signal(sig, SIG_IGN);
	write(STDERR_FILENO, "\n", 1);
	prompt();
	signal(SIGINT, handler);
}
