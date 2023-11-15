#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * search_and_execute - Searches for the command in the PATH and executes it
 * @args: Array of command and arguments
 *
 * This function is called when the specified command
 * is not executable in the current directory.
 * It searches for the command in the PATH, forks a child process,
 * and executes the command in the child process.
 */
void search_and_execute(char *args[])

{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path;

	while (dir != NULL)
	{
		full_path = build_full_path(dir, args[0]);

		if (access(full_path, X_OK) == 0)
		{
			execute_in_child(args, full_path);
			free(full_path);
			break;
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);

	if (dir == NULL)
	{
		printf("Command not found: %s\n", args[0]);
	}
}

/**
 * build_full_path - Builds the full path of the command
 * @dir: Directory from the PATH
 * @command: Command to be executed
 *
 * Returns: A pointer to the full path of the command.
 * The caller is responsible for freeing the allocated memory.
 */
char *build_full_path(char *dir, char *command)

{
	char *full_path = malloc(strlen(dir) + strlen(command) + 2);

	if (full_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}

/**
 * execute_in_child - Executes the command in the child process
 * @args: Array of command and arguments
 * @full_path: Full path of the command
 *
 * This function forks a child process
 * and executes the command in the child process.
 */
void execute_in_child(char *args[], char *full_path)

{
	pid_t child_pid = fork();
	int status;

	if (child_pid == -1)
	{
		perror("fork");
	}
	else if (child_pid == 0)
	{
		/* Child process */
		execve(full_path, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		waitpid(child_pid, &status, 0);
	}
}
