#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * find_command - finds the path of a given command
 * @command: the command to search for
 *
 * Return: the full path to the command, or NULL if not found
 */
char *find_command(char *command)
{
char *path_env = NULL;
char *path_copy, *dir;
char *full_path;
int i = 0;

/* Search for the PATH variable in the environment */

while (environ[i])
  {
  if (strncmp(environ[i], "PATH=", 5) == 0)
    {
      path_env = environ[i] + 5;
      break;
    }
  i++;
  }

 /* If PATH is not set or empty, return NULL */

 if (!path_env || path_env[0] == '\0')
   return (NULL);

 /* Split PATH into directories and check each one */
 
path_copy = strdup(path_env);
if (!path_copy)
  {
   perror("strdup");
   return (NULL);
  }

 dir = strtok(path_copy, ":");
while (dir)
{
  full_path = malloc(strlen(dir) + strlen(command) + 2); /* +2 for '/' and '\0' */
  if (!full_path)
    {
      perror("malloc");
       free(path_copy);
       return (NULL);
    }
  
sprintf(full_path, "%s/%s", dir, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (full_path); /* Command found */
}
 free(full_path); /* Free full_path before trying the next directory */
dir = strtok(NULL, ":");
}

free(path_copy);
return (NULL); /* Command not found */
}




/**
 * resolve_command_path - Resolves the full path of a command
 * @args: Array of command arguments

 * Return: Full path to the command if found, otherwise NULL
 */

char *resolve_command_path(char **args)
{
  char *cmd_path = NULL;
  /* If the command contains '/', assume it's an explicit path */
  if (strchr(args[0], '/'))
    {
      if (access(args[0], X_OK) == 0)
	 cmd_path = strdup(args[0]); /* Use the given path */
      else
	return (NULL);
    }
  else
    {
      /* If PATH is empty, check for commands that are not built-in */
      if (has_path_env() && strlen(getenv("PATH")) > 0)
	{
	  cmd_path = find_command(args[0]);
	}
      else
	{
	  /* If PATH is empty, only check if the user supplied a path */
	  if (access(args[0], X_OK) == 0)
	     cmd_path = strdup(args[0]);
	}
    }
  return (cmd_path);
}
