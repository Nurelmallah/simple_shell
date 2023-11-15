#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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
	size_t input_length;

	while (1)
	{
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input_length = strlen(input);

		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}

		if (strcmp(input, "exit") == 0)
		{
			break;
		}

		if (is_whitespace(input))
		{
			continue;
		}

		parse_input(input, args);
		execute_command(args);
	}

	return (0);
}

/**
 * is_whitespace - Checks if a string consists only of whitespace characters
 * @str: The input string
 *
 * Return: 1 if the string is whitespace-only, 0 otherwise
 */
int is_whitespace(const char *str)

{
	while (*str != '\0')
	{
		if (!isspace((unsigned char)*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}
