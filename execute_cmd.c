#include "shell.h"

int execute_cmd(char **args)
{
    pid_t pid;
    int status;

    if (!args[0])
        return (0);

    /* Handle exit built-in */
    if (strcmp(args[0], "exit") == 0)
        exit(0);

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "%s: command not found\n", args[0]);
            exit(127);
        }
    }
    else if (pid < 0)
    {
        /* Fork error */
        perror("hsh");
        return (1);
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }
    return (1);
}
