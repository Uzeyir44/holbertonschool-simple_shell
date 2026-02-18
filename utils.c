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

char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	if (!environ || !name)
		return (NULL);

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * _get_path - Finds command in PATH
 */
char *_get_path(char *command)
{
	char *path, *path_copy, *token, *file_path;
	struct stat st;

	if (!command)
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	path = _getenv("PATH");
	if (!path || strlen(path) == 0)
		return (NULL);
	path_copy = strdup(path);
	token = strtok(path_copy, ":");
	while (token)
	{
		file_path = malloc(strlen(token) + strlen(command) + 2);
		sprintf(file_path, "%s/%s", token, command);
		if (stat(file_path, &st) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * tokenize - Splits line into arguments
 */
char **tokenize(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);
	token = strtok(line, " \t\n\r");
	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n\r");
	}
	args[i] = NULL;
	return (args);
}

/**
 * free_args - Frees argument array
 */
void free_args(char **args)
{
	if (args)
		free(args);
}