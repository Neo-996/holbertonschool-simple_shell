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
 */
void execute_cmd(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return;

	/* Handle exit built-in */
	if (strcmp(args[0], "exit") == 0)
		handle_exit();

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("hsh");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
