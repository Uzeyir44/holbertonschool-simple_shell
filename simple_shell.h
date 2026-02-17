#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

/* deletes the \n from the end of command and returns it */
char *get_command();

/* returns path to our command */
char *get_path(char *command);

/* checks if the file exists */
int file_exists_and_executable(const char *path);

/* splits strings by delim */
char **split_string(char *str, char delim);

#endif