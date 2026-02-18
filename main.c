#include "simple_shell.h"

/**
 * main - Entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0
 */
int main(int ac, char **av)
{
	(void)ac;
	shell_loop(av[0]);
	return (0);
}

/**
 * shell_loop - Main loop
 * @prog_name: program name for errors
 */
void shell_loop(char *prog_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		args = tokenize(line);
		if (args && args[0])
		{
			if (handle_builtin(args, line, status) == -1)
				status = execute(args, prog_name);
			else
				status = 0;
		}
		free_args(args);
	}
	free(line);
}
