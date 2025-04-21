# hsh - Simple Shell

## Description
A basic UNIX command interpreter clone, mimicking the behavior of `/bin/sh`.

## Features
- Interactive and non-interactive modes
- Executes basic system commands
- Custom error printing (`./hsh: line: command: not found`)
- Betty-compliant C code

## Usage
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
./hsh

##..
