#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void execmd(char **argv);
char *find_location(char *command);// searches for location of the executive
int is_builtin(char *command);
void free_tokens(char **tokens);// frees memory

#endif