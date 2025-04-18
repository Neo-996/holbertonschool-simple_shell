#include "shell.h"

int execute_cmd(char **args)
{
    pid_t pid;
    int status;

    if (!args[0])
        return (0);

    if (strcmp(args[0], "exit") == 0)
        exit(0);

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror(args[0]);
            exit(127);
        }
    }
    else if (pid < 0)
    {
        perror("hsh");
        return (1);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
    }
    return (1);
}
