#include "shell.h"

/**
 * find_command - Finds a command in PATH
 * @command: Command to find
 * Return: Full path if found, NULL otherwise
 */
char *find_command(char *command)
{
    char *path, *dir, *full_path;
    struct stat st;

    /* Check if command exists as is */
    if (stat(command, &st) == 0)
        return (strdup(command));

    /* Get PATH environment variable */
    path = getenv("PATH");
    if (!path)
        return (NULL);

    /* Make copy of PATH to tokenize */
    path = strdup(path);
    dir = strtok(path, ":");

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);

        if (stat(full_path, &st) == 0)
        {
            free(path);
            return (full_path);
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path);
    return (NULL);
}
