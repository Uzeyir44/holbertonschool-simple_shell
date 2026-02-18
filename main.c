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
    size_t line_number = 1;
        
    while (1)
    {
        printf("$ ");
    
        command = get_command();

        if (command == NULL)
            break;

        if (strlen(command) == 0)
        {
            line_number++;
            free(command);
            continue;
        }

        full_path = get_path(command);

        if (full_path == NULL)
            fprintf(stderr, "%s: %zu: %s: not found\n", argv[0], line_number, command);
        else
        {
            int pid = fork();

            if (pid == 0)
            {
                char *args[] = {command, NULL};
                extern char **environ;
                execve(full_path, args, environ);
            }
            else
            {
                waitpid(pid, NULL, 0);
            }

            free(full_path);
        }

        free(command);
        line_number++;

    }
}
