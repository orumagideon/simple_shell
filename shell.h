#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
extern int dircount;

#define DELIM " \n\t"

/* void prototypes */
void prompt(void);
void loop(char **env);
void handler(int sig);
void env(char **env);

/* char prototypes */
char *_strdup(char *str);
char *get_line(void);
char **split_line(char *line);
char *get_env(char **env);
char *path_cat(char *dir, char *av);
char **dirTok(char **env);
char *checkPath(char **dir, char *command);

/* int prototypes */
int _strcmp(char *strng1, char *strng2);
int _strlen(char *s);
int execute(char *fullPath, char **command);
int exit_sh(char **command);
int cd(char **command);
int printenv(char **command);
int checkBuiltins(char *combine, char **command);

/*free buffer */
void buffers1(char *line, char **command);
void buffers2(char **dir, char *combine);
void buffers3(char **tokens, char *buf);
void buffers4(char **tok, char *buf2);
void buffers5(char *dup);

#endif
