#include "shell.h"

/**
 * handler - Function determines a signal.
 * @sig: The signal
 * Return: void
 */
void  handler(int sig)
{
	signal(sig, SIG_IGN);
	write(STDERR_FILENO, "\n", 1);
	prompt();
	signal(SIGINT, handler);
}
