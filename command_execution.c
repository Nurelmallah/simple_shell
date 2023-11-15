#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * execute_command - executes commands,
 * searches PATH if no command location given
 * @arguments: parsed arguments buffer
 * @path: parsed buffer of PATH
 * @program_name: name of program
 * @input_count: number of user input
 */
void execute_command(char **arguments, char **path,
		char *program_name, int input_count)
{
	int i = 0;
	size_t path_space = 31, len = custom_strlen(arguments[0]) + path_space + 1;
	char *buffer_path;

	if (contains_slash(arguments[0]))
	{
		handle_slash_command(arguments, program_name, input_count);
	}
	else
	{
		buffer_path = prepare_buffer_path(arguments, path,
			path_space, len, program_name, input_count);
		search_and_execute(buffer_path, arguments);
	}

	free(buffer_path);
}

/**
 * handle_slash_command - handles execution
 * when the command contains a slash
 * @arguments: parsed arguments buffer
 * @program_name: name of program
 * @input_count: number of user input
 */
void handle_slash_command(char **arguments, char *program_name,
		int input_count)
{
	if (execve(arguments[0], arguments, NULL) == -1)
	{
		print_error("%s: %d: %s: not found\n",
				program_name, input_count, arguments[0]);
		_exit(127);
	}
}
