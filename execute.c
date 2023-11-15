#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_in_child - Executes the command in a child process.
 * @args: Array of command and arguments
 * @full_path: Full path to the command
 */
void execute_in_child(char *args[], char *full_path)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		execve(full_path, args, NULL);
		perror("execve");
		_exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		wait(&status);
	}
}
