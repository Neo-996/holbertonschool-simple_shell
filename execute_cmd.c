#include "shell.h"

int shell_exit(char **args)
{
    (void)args;
    exit(0);
}

int execute_cmd(char **args)
{
    pid_t pid;
    int status;

    if (!args[0])
        return (0);

    /* Handle exit built-in */
    if (strcmp(args[0], "exit") == 0)
        return (shell_exit(args));

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "%s: %s\n", args[0], strerror(errno));
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
