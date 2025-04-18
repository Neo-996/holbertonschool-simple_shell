#include "shell.h"

/**
 * execute_cmd - Executes a command
 * @args: Argument vector
 * Return: Exit status
 */
int execute_cmd(char **args)
{
    pid_t pid;
    int status;
    char *cmd;

    if (!args[0])
        return (1);

    if (strcmp(args[0], "exit") == 0)
        exit(0);

    /* Find command in PATH */
    cmd = find_command(args[0]);
    if (!cmd)
    {
        fprintf(stderr, "%s: command not found\n", args[0]);
        return (127);
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd, args, environ) == -1)
        {
            perror(args[0]);
            free(cmd);
            exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
        free(cmd);
        return (1);
    }
    else
    {
        waitpid(pid, &status, 0);
        free(cmd);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }
    return (1);
}
