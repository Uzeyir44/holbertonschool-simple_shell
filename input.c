#include "simple_shell.h"

/**
 * get_command - Reads a line from stdin using getline
 *
 * Return: pointer to the line (must be freed), or NULL on EOF/error
 */
char *get_command(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t nread;

    nread = getline(&line, &n, stdin);
    if (nread == -1)
        return NULL;

    if (nread > 0 && line[nread - 1] == '\n')
        line[nread - 1] = '\0';
    return line;
}
