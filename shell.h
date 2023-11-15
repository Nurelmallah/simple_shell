#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BUFF_SIZE 1024

extern char **environ;

/* Function declarations */
void execute_command(char **arguments, char **path,
		char *program_name, int input_count);
void handle_slash_command(char **arguments,
		char *program_name, int input_count);
char *prepare_buffer_path(char **arguments, char **path,
		size_t path_space, size_t len, char *program_name, int input_count);
void search_and_execute(char *buffer_path, char **arguments);

char **tokenize_input(char *input, char *delimiter);

int exit_shell(char **args, char *program_name, int input_count);
int print_environment(char **args, char *program_name, int input_count);
int unset_environment(char **args, char *program_name, int input_count);
int change_directory(char **args, char *program_name, int input_count);

char *create_env_buffer(const char *key, const char *value);
int set_environment(char **args, char *program_name, int input_count);

void get_prompt(void);

#endif /* SHELL_H */
