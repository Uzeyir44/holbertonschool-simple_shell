#include "simple_shell.h"

/**
 * execute - Forks and executes command
 * Return: Exit status of the command
 */
int execute(char **args, char *prog_name)
{
	int pid;
	int status;
	char *full_path;

	full_path = _get_path(args[0]);
	if (!full_path)
	{
		print_error(prog_name);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error");
		if (full_path != args[0])
			free(full_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("Execve Error");
			exit(2);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}

	if (full_path != args[0])
		free(full_path);
	return (status);
}

/**
 * print_error - Prints error in shell format
 */
void print_error(char *prog_name)
{
	fprintf(stderr, "%s: No such file or directory\n", prog_name);
}