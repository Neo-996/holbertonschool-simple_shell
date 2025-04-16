#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Global environment pointer */
extern char **environ;

/* Function Prototypes */
void execute_cmd(char *line, char *prog_name, int line_num);
void tokenize_input(char *line, char ***args);
void free_args(char **args);
void print_error(char *prog_name, int line_num, char *command);

#endif /* SHELL_H */
