#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 100

void display_prompt(void);
void parse_input(char *input, char *args[]);
void execute_command(char *args[]);
void search_and_execute(char *args[]);
char *build_full_path(char *dir, char *command);
void execute_in_child(char *args[], char *full_path);
ssize_t read_buf(char *buf, size_t *len);

/**
 * is_whitespace - used to check if a string consists only of whitespace characters
 * @str: The input string that is used used.
 * Return: 1 if the string is whitespace-only, 0 otherwise
 */
int is_whitespace(const char *str);

#endif
