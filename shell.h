#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* external variable to access the environment list */
extern char **environ;

/* Function Prototypes */
int execute_cmd(char **args);
int run_command(char *cmd_path, char **args);
char *find_command(char *command);
char *resolve_command_path(char **args);
char **parse_line(char *line);
int has_path_env(void);

  
#endif /* SHELL_H */
