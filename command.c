#include "simple_shell.h"

/**
 * run_command - forks and executes a single-word command
 * @command: absolute or relative path of command
 * @shell_name: name of shell (for error messages)
 */
void run_command(char *command, char *shell_name)
{
    char *full_path;
    int pid;

    if (!file_exists_and_executable(command))
    {
        fprintf(stderr, "%s: No such file or directory\n", shell_name);
        return;
    }

    full_path = strdup(command);
    if (!full_path)
        return;
    pid = fork();
    if (pid == 0)
    {
        char *args[2];
        extern char **environ;

        args[0] = command;
        args[1] = NULL;

        execve(full_path, args, environ);
        perror("execve");
        free(full_path);
        exit(1);
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
    else
    {
        perror("fork");
    }

    free(full_path);
}
