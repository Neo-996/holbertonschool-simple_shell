#include "shell.h"

/**
 * print_error - formats and prints command error
 * @prog_name: name of shell
 * @line_num: line number
 * @command: the command not found
 */
void print_error(char *prog_name, int line_num, char *command)
{
  fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_num, command);
}

/**
 * free_args - Frees a NULL-terminated array of strings
 * @args: The array to free
 */
void free_args(char **args)
{
   int i = 0;

   if (!args)
     return;

   while (args[i])
     {
       free(args[i]);
       i++;
     }
   free(args);
}
