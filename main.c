#include "simple_shell.h"

int main(int argc, char **argv)
{
    char *command;
    (void)argc;

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("$ ");
            fflush(stdout); /* prompt shows immediately */
        }

        command = get_command();
        if (!command)
            break; /* EOF (Ctrl+D) */

        if (strlen(command) == 0)
        {
            free(command);
            continue; /* ignore empty input */
        }

        run_command(command, argv[0]);
        free(command);
    }

    return 0;
}
