#include "simple_shell.h"

/**
 * file_exists_and_executable - Checks if a file exists and is executable
 * @path: file path
 *
 * Return: 1 if exists & executable, 0 otherwise
 */
int file_exists_and_executable(const char *path)
{
    if (!path)
        return 0;
    return (access(path, X_OK) == 0);
}
