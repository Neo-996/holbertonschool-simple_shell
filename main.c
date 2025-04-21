#include "shell.h"

/**
 * main - Entry point of the shell
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}
		args = parse_line(line);
		if (args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				int exit_status = status;

				if (args[1])
					exit_status = atoi(args[1]);
				free(line);
				free(args);
				exit(exit_status);
			}
			status = execute_cmd(args);
		}
		free(args);
		if (status == 2)
		{
			free(line);
			exit(2);
		}
	}
	return (status);
}
