#include "shell.h"

/**
 * find_command - Locates the full path of a specified command
 * @command: the name of the command to find
 *
 * Return: full path to the command if found, otherwise NULL
 */
char *find_command(char *command)
{
char *path_env = NULL; /* holds the PATH environment variable */
char *path_copy, *dir; /* for duplicating and splitting the PATH string */
char full_path[1024];  /* buffer for constructing full command paths */
int i = 0;

/* search PATH manually inside environ */

while (environ[i])
{
if (strncmp(environ[i], "PATH=", 5) == 0)
{
path_env = environ[i] + 5; /* skip "PATH=" and point to the actual value */
break;
}
i++;
}

/* Stop if PATH variable wasn't found */
if (!path_env)
return (NULL);

/* Duplicate PATH to safely manipulate it */
path_copy = strdup(path_env);
dir = strtok(path_copy, ":"); /* separate PATH into directories using ':' */

/* Go through each directory in PATH */
while (dir)
{
	sprintf(full_path, "%s/%s", dir, command); 

	if (access(full_path, X_OK) == 0)
	{
		free(path_copy);
		return (strdup(full_path));
	}
	dir = strtok(NULL, ":"); /* move to next directory in the PATH list */
}

/* Command not found in any PATH directory */
free(path_copy);
return (NULL);
}




/**
 * has_path_env - Determines if the environment contains a PATH variable
 *
 * Return: 1 if PATH is found, 0 otherwise
 */

int has_path_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	/* PATH variable is not present */
	return (0);
}
