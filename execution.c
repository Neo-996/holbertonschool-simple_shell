#include "shell.h"


int run_command(char *cmd_path, char **args);

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 * Return: 127 if command not found, 0 otherwise
 */
int execute_cmd(char **args)
{
int status;
char *cmd_path;

if (args[0] == NULL)
return (0);
/* Built-in: env */
if (strcmp(args[0], "env") == 0)
{
int i = 0;
while (environ[i])
printf("%s\n", environ[i++]);
return (0);
}
/* Check if command contains '/' */
if (strchr(args[0], '/'))
{
if (access(args[0], X_OK) == 0)
cmd_path = strdup(args[0]);
else
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return (127);
}
}
else
{
/* No '/', resolving using PATH */
cmd_path = find_command(args[0]);
if (cmd_path == NULL)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
return (127);
}
}
/* Fork and execute */
status = run_command(cmd_path, args);
free(cmd_path);
return (status);
}

/**
 * run_command - Forks and executes the command
 * @cmd_path: Resolved command path
 * @args: Argument vector
 * Return: Exit status
 */
int run_command(char *cmd_path, char **args)
{

pid_t pid;
int status;

pid = fork();

if (pid == 0)
{
if (execve(cmd_path, args, environ) == -1)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
if (cmd_path != NULL)
{
free(cmd_path);
}
exit(127);
}
}
else if (pid < 0)
{
perror("fork");
return (1);
}
else
{
waitpid(pid, &status, 0);
if (WIFEXITED(status))
status = WEXITSTATUS(status);
else
status = 1;
}
if (cmd_path != NULL)
{
free(cmd_path);
}
return (1);
}
