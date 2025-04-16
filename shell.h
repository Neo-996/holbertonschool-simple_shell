#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Global environment pointer */
extern char **environ;

/* Function Prototypes */
char **parse_line(char *line);
void execute_cmd(char **args);
extern char **environ;
char *find_command(char *command);

#endif /* SHELL_H */
