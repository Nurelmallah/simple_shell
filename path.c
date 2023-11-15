#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * build_full_path - Builds the full path to a command.
 * @dir: Directory to search for the command
 * @command: Command to execute
 * Return: The full path to the command
 */
char *build_full_path(char *dir, char *command)
{
	size_t dir_len = strlen(dir);
	size_t command_len = strlen(command);

	char *full_path = malloc(dir_len + command_len + 2);

	if (full_path == NULL)
	{
		perror("malloc");
		_exit(EXIT_FAILURE);
	}

	strcpy(full_path, dir);

	if (full_path[dir_len - 1] != '/')
	{
		strcat(full_path, "/");
	}

	strcat(full_path, command);

	return (full_path);
}
