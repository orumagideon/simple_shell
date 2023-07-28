#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

/*global*/
extern char **environ;
extern int dircount;

#define DELIM " \n\t"

/*int prototypes */
int cd(char **command);
int printenv(char **command);
int exit_sh(char **command);
int _strlen(char *s);
int _strcmp(char *strng1, char *strng2);
int checkBuiltins(char *combine, char **command);
int execute(char *fullPath, char **command);

/*char prototypes */
char *_strdup(char *str);
char *get_line(void);
char **split_line(char *line);
char *get_env(char **env);
char *pathCat(char *dir, char *av);
char **dirTok(char **env);
char *checkPath(char **dir, char *command);

/* void prototypes */
void loop(char **env);
void prompt(void);
void env(char **env);
void handler(int sig);
void buffers1(char *line, char **command);
void buffers2(char **dir, char *combine);
void buffers3(char **tokens, char *buf);
void buffers4(char **tok, char *buf2);
void buffers5(char *dup);
#endif
