#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **args = NULL;
    int status = 0;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "($) ", 4);

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (interactive)
                write(STDOUT_FILENO, "\n", 1);
            free(line);
            exit(status);
        }

        /* Remove newline */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        args = parse_line(line);
        if (args && args[0])
            status = execute_cmd(args);

        free(args);
        args = NULL;
    }

    /* Never reached but included for completeness */
    free(line);
    return (status);
}
