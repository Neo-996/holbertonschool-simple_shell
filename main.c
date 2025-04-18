#include "shell.h"

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
			exit(status);
		}

		args = parse_line(line);
		if (args[0] != NULL)
			status = execute_cmd(args);

		free(args);
	}

	free(line);
	return (status);
}
