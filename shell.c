#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Executes a command with arguments
 * @args: Array of command and arguments
 *
 * Return: 1 if shell should continue, 0 if it should terminate
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
    {
        return (1); /* Empty command */
    }

    /* Check for exit built-in */
    if (strcmp(args[0], "exit") == 0)
    {
        return (0); /* Signal to exit shell */
    }

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Forking error */
        perror("Error");
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}

/**
 * parse_input - Parses input into arguments
 * @input: User input string
 *
 * Return: Array of arguments
 */
char **parse_input(char *input)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return (tokens);
}

/**
 * read_input - Reads input from user
 *
 * Return: Input string
 */
char *read_input(void)
{
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t chars_read;

    chars_read = getline(&input, &bufsize, stdin);
    if (chars_read == -1)
    {
        if (feof(stdin))
        {
            free(input);
            exit(EXIT_SUCCESS); /* Handle EOF (Ctrl+D) */
        }
        else
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
    }

    return (input);
}

/**
 * main - Main shell loop
 *
 * Return: Exit status
 */
int main(void)
{
    char *input;
    char **args;
    int status = 1;

    do {
        printf("$ "); /* Display prompt */
        input = read_input();
        args = parse_input(input);
        status = execute_command(args);

        free(input);
        free(args);
    } while (status);

    return (EXIT_SUCCESS);
}
