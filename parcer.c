#include "shell.h"
#include <string.h>

/**
 * parse_input - Tokenizes input into arguments
 * @input: User input string
 * @args: Array to store arguments
 *
 * This function takes a user input string and tokenizes it into
 * individual arguments, storing them in the provided array.
 */

void parse_input(char *input, char *args[])
{
	int arg_count = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
}
