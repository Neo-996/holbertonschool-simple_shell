#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

/* Function prototypes */
char **parse_line(char *line);
int execute_cmd(char **args);
int shell_exit(char **args);

#endif /* SHELL_H */
