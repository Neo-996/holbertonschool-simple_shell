#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    char **args = NULL;
    int status = 0;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "($) ", 4);

        if (getline(&line, &len, stdin) == -1)
        {
            free(line);
            line = NULL;
            if (interactive)
                write(STDOUT_FILENO, "\n", 1);
            exit(status);
        }

        /* Remove newline */
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        args = parse_line(line);
        if (args && args[0])
            status = execute_cmd(args);

        /* Clean up */
        free(args);
        args = NULL;
        free(line);
        line = NULL;
        len = 0;
    }

    /* Should never reach here */
    if (line) free(line);
    if (args) free(args);
    return (status);
}
