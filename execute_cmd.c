#include "shell.h"

/**
 * execute_cmd - Executes a command using fork and exec
 * @line: The full input line (already tokenized outside)
 * @program_name: The name of the shell program (for error messages)
 * @line_num: The current line number (for error messages)
 */
void execute_cmd(char *line, char *program_name, int line_num)
{
  pid_t pid;
  int status;
  char **args;

  tokenize_input(line, &args);

  if (!args || !args[0])
    {
      free_args(args);
      return;
    }
  pid = fork();
  if (pid == -1)
    {
      perror("fork failed");
        free_args(args);
	exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      /* Child process */
       execvp(args[0], args);
       /* If execvp returns, it must have failed */
       fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, args[0]);
       free_args(args);
       exit(127);
    }
  else
    {
      /* Parent process */
      waitpid(pid, &status, 0);
      free_args(args);
    }
