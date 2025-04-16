#include "shell.h"

/**
 * tokenize_input - Splits line into tokens (args)
 * @line: user input
 * @args: pointer to array of strings (tokens)
 */
void tokenize_input(char *line, char ***args)
{
  char *token;
  int bufsize = 64, i = 0;

   /* Allocate memory for the arguments array */
  *args = malloc(sizeof(char *) * bufsize);
  if (!*args)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

  /* Tokenize the input line */
  token = strtok(line, " \t\r\n");
  while (token != NULL)
    {
      (*args)[i++] = token;

      /* If we run out of space in the array, reallocate */
      if (i >= bufsize)
	{
	  bufsize += 64;  /* Increase buffer size */
	   *args = realloc(*args, sizeof(char *) * bufsize);
	   if (!*args)
	     {
	       perror("realloc");
	       exit(EXIT_FAILURE);
	     }
	}

      token = strtok(NULL, " \t\r\n");  /* Get the next token */
    }
  (*args)[i] = NULL;  /* Null-terminate the array of strings */
}
