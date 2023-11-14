#include "shell.h"
#include <string.h>
#include <unistd.h>

/**
 * main - Entry point of the shell program
 *
 * This function handles the main loop of the shell, taking user input,
 * parsing it, and executing the corresponding command.
 *
 * Return: 0 for successful execution
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	char *args[MAX_INPUT_SIZE];

	while (1)
	{
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		size_t input_length = strlen(input);

		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}

		if (strcmp(input, "exit") == 0)
		{
			break;
		}

		parse_input(input, args);
		execute_command(args);
	}

	return (0);
}
