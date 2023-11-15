#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * prepare_buffer_path - prepares the buffer path for non-slash commands
 * @arguments: parsed arguments buffer
 * @path: parsed buffer of PATH
 * @path_space: size limit for PATH
 * @len: length of the buffer path
 * @program_name: name of program
 * @input_count: number of user input
 * Return: the allocated buffer path
 */
char *prepare_buffer_path(char **arguments, char **path,
	size_t path_space, size_t len, char *program_name, int input_count)
{
	int i = 0;
	char *buffer_path = malloc(len * sizeof(char));

	if (buffer_path == NULL)
		exit(EXIT_FAILURE);

	for (; path[i]; i++)
	{
		if ((custom_strlen(path[i])) >= path_space)
		{
			buffer_path = custom_realloc(buffer_path, len, custom_strlen(path[i]));

			if (buffer_path == NULL)
				exit(EXIT_FAILURE);
		}

		custom_strcpy(buffer_path, path[i]);
		custom_strcat(buffer_path, "/");
		custom_strcat(buffer_path, arguments[0]);

		if (execve(buffer_path, arguments, NULL) != -1)
			break;
	}

	if (path[i] == NULL)
	{
		print_error("%s: %d: %s: not found\n",
			program_name, input_count, arguments[0]);
		_exit(1);
	}

	return (buffer_path);
}

/**
 * search_and_execute - searches for the command in the PATH and executes it
 * @buffer_path: the buffer path containing the full path to the command
 * @arguments: parsed arguments buffer
 */
void search_and_execute(char *buffer_path, char **arguments)
{
	if (execve(buffer_path, arguments, NULL) == -1)
	{
		print_error("Error executing command: %s\n", strerror(errno));
		_exit(1);
	}
}
