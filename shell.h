#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Declare environ if not available */
extern char **environ;

/* Function prototypes */
char **parse_line(char *line);
int execute_cmd(char **args);
char *find_command(char *command);

#endif /* SHELL_H */
