#include "shell.h"
/**
 *buffers1 - function frees line and command
 *@line: the pointer to line
 *@command: the command
 *Return: void
 */
void buffers1(char *line, char **command)
{
	static char *l;
	static char **cmd;

	if (!line && !command)
	{
		{
			if (l)
				free(l);
			if (cmd)
				free(cmd);
		}
		if (line)
		{
			if (l)
				free(l);
			l = line;
		}
		if (command)
		{
			if (cmd)
				free(cmd);
			cmd = command;
		}
	}
}

/**
 *buffers2 - function frees directory and combine
 *@dir: the directory
 *@combine: combine
 *Return: void
 */
void buffers2(char **dir, char *combine)
{
	static char **di;
	static char *co;

	if (!dir && !combine)
	{
		if (di)
			free(di);
		if (co)
			free(co);
	}
	if (dir)
	{
		if (di)
			free(di);
		di = dir;
	}
	if (combine)
	{
		if (co)
			free(co);
		co = combine;
	}
}
/**
 *buffers3 - function frees token and buffer
 *@tokens: tokens
 *@buf: buffer
 *Return: void
 */
void buffers3(char **tokens, char *buf)
{
	static char **tokn;
	static char *bu;

	if (!tokens && !buf)
	{
		if (tokn)
			free(tokn);
		if (bu)
			free(bu);
	}
	if (tokens)
	{
		if (tokn)
			free(tokn);
		tokn = tokens;
	}
	if (buf)
	{
		if (bu)
			free(bu);
		bu = buf;
	}
}
/**
 *buffers4 - function frees tok and buf2
 *@tok: the token
 *@buf2: the buffer
 *Return: void
 */
void buffers4(char **tok, char *buf2)
{
	static char **to;
	static char *b2;

	if (!tok && !buf2)
	{
		if (to)
			free(to);
		if (b2)
			free(b2);
	}
	if (tok)
	{
		if (to)
			free(to);
		to = tok;
	}
	if (buf2)
	{
		if (b2)
			free(b2);
		b2 = buf2;
	}
}

/**
 *buffers5 - function frees dup buffer
 *@dup: the buffer found in strlen
 *Return: void
 */
void buffers5(char *dup)
{
	static char *du;

	if (!dup)
	{
		if (du)
			free(du);
	}
	if (dup)
	{
		if (du)
			free(du);
		du = dup;
	}
}
