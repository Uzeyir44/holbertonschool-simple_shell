#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* input.c */
char *get_command(void);

/* utils.c */
int file_exists_and_executable(const char *path);

/* command.c */
void run_command(char *command, char *shell_name);

#endif
