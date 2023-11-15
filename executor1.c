#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * execute_command - Executes the given command
 * @args: Array of command and arguments
 *
 * This function checks if the specified command is executable,
 * searches for the command in the PATH, forks a child process,
 * and executes the command in the child process.
 */
void execute_command(char *args[])
{
	pid_t child_pid;
	int status;

	/* Check if the specified command is executable */
	if (access(args[0], X_OK) == 0)
	{
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
		}
		else if (child_pid == 0)
		{
			/* Child process */
			execve(args[0], args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			waitpid(child_pid, &status, 0);
		}
	}
	else
	{
		search_and_execute(args);
	}
}
