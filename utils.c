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
