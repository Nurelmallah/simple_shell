#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 100

void display_prompt(void);
void parse_input(char *input, char *args[]);
void execute_command(char *args[]);

#endif
