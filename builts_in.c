#include "simple_shell.h"

/**
 * handle_builtin - Handles shell built-in commands
 * @args: Tokenized arguments
 * @line: Line buffer to free if exiting
 * @status: Current exit status
 * Return: 0 if a built-in was handled, -1 otherwise
 */
int handle_builtin(char **args, char *line, int status)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(status);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (0);
	}

	return (-1);
}