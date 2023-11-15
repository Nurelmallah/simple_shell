#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * search_and_execute - Searches for the command in the directories of the PATH
 * and executes it if found.
 * @args: Array of command and arguments
 */
void search_and_execute(char *args[])
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	char *full_path;

	while (token != NULL)
	{
		full_path = build_full_path(token, args[0]);

		if (access(full_path, X_OK) == 0)
		{
			execute_in_child(args, full_path);
			free(full_path);
			return;
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	perror("Command not found");
	_exit(EXIT_FAILURE);
}
