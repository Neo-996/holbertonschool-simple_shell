#include "shell.h"

/**
 * handle_exit - Handles the exit built-in command
 */
static void handle_exit(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * execute_cmd - Executes a command
 * @args: Argument vector
 * Return: Exit status of the command
 */
int execute_cmd(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (0);

	/* Handle exit built-in */
	if (strcmp(args[0], "exit") == 0)
		handle_exit();

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("hsh");
			exit(127);  /* Command not found */
		}
	}
	else if (pid < 0)
	{
		perror("hsh");
		return (1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (0);
}
