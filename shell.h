#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

typedef struct info
{
    char **argv;
    char **env;
    char *line;
    int argc;
    int readfd;
    int status;
    int err_num;
} info_t;

/* main.c */
int main(int argc, char *argv[], char **env);

/* functions.c */
int interactive(info_t *info);
void display_prompt(int newline);
int get_line(info_t *info);
void parse_line(info_t *info);
void execute_line(info_t *info);
void init_info(info_t *info, char **env);
void free_info(info_t *info);

/* builtins.c */
int _myexit(info_t *info);
int _myenv(info_t *info);

#endif /* SHELL_H */
