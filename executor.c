#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Executes the given command
 * @args: Array of command and arguments
 *
 * This function checks if the specified command is executable,
 * forks a child process, and executes the command in the child process.
 */
void execute_command(char *args[])
{
	if (access(args[0], X_OK) == 0)
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			_exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			execve(args[0], args, NULL);
			perror("execve");
			_exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			wait(&status);
		}
	}
	else
	{
		perror("Command not found");
		_exit(EXIT_FAILURE);
	}
}
