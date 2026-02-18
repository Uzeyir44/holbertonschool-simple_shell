#include "simple_shell.h"

char *get_command()
{
    char *line = NULL;
    size_t n = 0;
    ssize_t nread = getline(&line, &n, stdin);

    if (nread == -1)
        return (NULL);

    if (nread > 0)
        line[nread - 1] = '\0';
    
    return (line);
}

int file_exists_and_executable(const char *path)
{
    return (access(path, X_OK) == 0);
}

char **split_string(char *str, char delim)
{
    char **result = NULL;
    size_t count = 0;
    char *tmp = str;
    char *token;
    char delim_str[2] = {delim, '\0'};
    size_t i;
    size_t j;

    if (!str)
        return NULL;

    while (*tmp)
    {
        if (*tmp == delim)
            count++;
        tmp++;
    }
    count++;

    result = malloc((count + 1) * sizeof(char *));
    if (!result)
        return NULL;

    i = 0;
    token = strtok(str, delim_str);
    while (token)
    {
        result[i] = malloc(strlen(token) + 1);
        if (!result[i])
        {
            for (j = 0; j < i; j++)
                free(result[j]);
            free(result);
            return NULL;
        }
        strcpy(result[i], token);
        i++;
        token = strtok(NULL, delim_str);
    }

    result[i] = NULL;
    return result;
}

void free_split(char **dirs)
{
    int i;

    if (dirs == NULL)
        return;

    for (i = 0; dirs[i] != NULL; i++)
    {
        free(dirs[i]);
    }

    free(dirs);
}

char *get_path(char *command)
{
    char *path_env = strdup(getenv("PATH"));
    char **dirs = split_string(path_env, ':');
    char full_path[1024];
    int i;
    char *result;

    for (i = 0; dirs[i] != NULL; i++)
    {
        sprintf(full_path, "%s/%s", dirs[i], command);

        if (file_exists_and_executable(full_path))
        {
            result = malloc(strlen(full_path) + 1);
            strcpy(result, full_path);
            free_split(dirs);
            free(path_env);
            return (result);
        }
    }

    free_split(dirs);
    free(path_env);
    return (NULL);
}

