#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* utils.c */
int file_exists_and_executable(const char *path);

/* command.c */
void run_command(char *command, char *shell_name);

/* finds the path of the command*/
char *_get_path(char *command);

/*returns the environment */
char *_getenv(const char *name);

/* splits path and collects them into array */
char **tokenize(char *line);

/* frees array */
void free_args(char **args);

/* the core logic of shell */
void shell_loop(char *prog_name);

/* prints the error message */
void print_error(char *prog_name);

/* handles manual exit and env */
int handle_builtin(char **args, char *line, int status);

/* executes command */
int execute(char **args, char *prog_name);

#endif
