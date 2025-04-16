#include "shell.h"

/**
 * main - Simple shell entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int line_num = 0;
  char **args;
  (void)argc;

  while (1)
    {
      line_num++;

      if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "$ ", 2);

      nread = getline(&line, &len, stdin);
      if (nread == -1)
	{
	  if (isatty(STDIN_FILENO))
	    write(STDOUT_FILENO, "\n", 1);
	  break;
	}
      if (line[nread - 1] == '\n')
	line[nread - 1] = '\0';
      
      tokenize_input(line, &args); /* passing pointer to array */
      if (!args || !args[0])
	{
	  free_args(args);
	  continue;
	}
      
      execute_cmd(args, argv[0], line_num);
      free_args(args);
    }
  free(line);
    return (0);
}
