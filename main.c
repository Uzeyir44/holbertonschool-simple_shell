#include "simple_shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv)
{
    char *command;
    char *full_path;
    (void)argc;
        
    while (1)
    {
        printf("$ ");
    
        command = get_command();

        if (command == NULL)
            break;

        if (strlen(command) == 0)
        {
            free(command);
            continue;
        }

        full_path = get_path(command);

        if (full_path == NULL)
            fprintf(stderr, "%s: No such file or directory\n", argv[0]);
        else
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[2];
                extern char **environ;
                args[0] = command;
                args[1] = NULL;
                execve(full_path, args, environ);
            }
            else
            {
                waitpid(pid, NULL, 0);
            }

            free(full_path);
        }

        free(command);
    }

    return (0);
}
