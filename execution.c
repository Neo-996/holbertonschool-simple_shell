#include "shell.h"

/**
 * handle_builtins - Identifies and runs built-in commands
 * @args: Array of command arguments
 * Return: 1 if a built-in command was executed, 0 if not
 */
int handle_builtins(char **args)
{
	int i;

	/* Process the built-in "exit" command */
	if (strcmp(args[0], "exit") == 0)
		exit(0);
	/* Process the built-in "env" command */
	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i]; i++)
			printf("%s\n", environ[i]);
		return (1); /* Indicates a built-in command was executed */
	}

	return (0); /* Not a built-in command */
}

/**
  * resolve_command_path - Finds the full path of a command
 * @args: Array of command arguments
 * Return: Full path to the command if found, otherwise NULL
 */
char *resolve_command_path(char **args)
{
	char *cmd_path = NULL;

	/* If the command contains '/', assume it's a path */
	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
			cmd_path = strdup(args[0]); /* Use the given path */
		else
			return (NULL);
	}
	else
	{
		/* Free memory used for command path */
		cmd_path = find_command(args[0]);
	}

	return (cmd_path);
}

/**
 * run_command - Forks and executes a command
 * @cmd_path: Full path to command
 * @args: Argument vector
 * Return: Command exit status or 0
 */
int run_command(char *cmd_path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		/* Child process: Execute the command */
	  if (execve(cmd_path, args, environ) == -1) /* if execve fails */
	    {
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		free(cmd_path);
		exit(127); /* Return 127 when the command is not found */
	    }
	    }
	else if (pid < 0)
	{
		/* Fork failed */
		perror("fork");
	}
	else
	{
		/* Parent process: Wait for the child to finish */
		if (waitpid(pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}

	return (0); /* Return 0 if the command was executed successfully */
}

/**
 * execute_cmd - Executes a command with path resolution
 * @args: Argument vector (command and its arguments)
 * Return: 127 if command not found, or exit status
 */
int execute_cmd(char **args)
{
	char *cmd_path;
	int exit_status = 0;

	if (args[0] == NULL)
		return (0);

	/* Check and handle built-in commands */
	if (handle_builtins(args))
		return (0);

	/* Resolve the full path of the command */
	cmd_path = resolve_command_path(args);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		return (127); /* Return 127 if command not found */
	}

	exit_status = run_command(cmd_path, args);

	if (cmd_path != NULL)
	{
		free(cmd_path);
		cmd_path = NULL;
	}

	return (exit_status);
}
