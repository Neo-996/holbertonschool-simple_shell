#include "shell.h"

/**
 * handle_builtins - Handles built-in commands
 * @args: Argument vector
 * Return: 1 if builtin handled, 0 otherwise
 */
static int handle_builtins(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		exit(0);

	if (strcmp(args[0], "env") == 0)
	{
		int i = 0;

		while (environ[i])
			printf("%s\n", environ[i++]);
		return (1);
	}

	return (0);
}

/**
 * resolve_command_path - Finds the full path of a command
 * @command: Command to find
 * Return: Allocated string with full path, or NULL if not found
 */
static char *resolve_command_path(char *command)
{
	char *cmd_path;

	if (access(command, X_OK) == 0)
		return (strdup(command));

	cmd_path = find_command(command);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
		exit(127);
	}

	return (cmd_path);
}

/**
 * execute_child_process - Handles the child process execution
 * @cmd_path: Full path to command
 * @args: Argument vector
 */
static void execute_child_process(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		free(cmd_path);
		exit(127);
	}
}

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 */
void execute_cmd(char **args)
{
	pid_t pid;
	char *cmd_path;
	int status;

	if (args[0] == NULL)
		return;

	if (handle_builtins(args))
		return;

	cmd_path = resolve_command_path(args[0]);

	pid = fork();
	if (pid == 0)
	{
		execute_child_process(cmd_path, args);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
	}
}
