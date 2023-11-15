#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * tokenize_input - uses strtok to tokenize input and store in a buffer
 * @input: user input from getline()
 * @delimiter: set delimiter for tokenizer
 * Return: pointer to strings of tokens
 */
char **tokenize_input(char *input, char *delimiter)
{
	size_t i = 0, buffer_size = BUFF_SIZE, new_size;
	char *token;
	char **tokens = malloc(buffer_size * sizeof(char *));

	if (tokens == NULL)
		return (NULL);

	token = custom_strtok(input, delimiter);

	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= buffer_size)
		{
			new_size = buffer_size * 2;
			tokens = custom_realloc(tokens, buffer_size * sizeof(char *),
					new_size * sizeof(char *));

			if (tokens == NULL)
			{
				print_error("Error: memory allocation\n");
				exit(EXIT_FAILURE);
			}

			buffer_size = new_size;
		}

		token = custom_strtok(NULL, delimiter);
	}

	tokens[i] = NULL;
	return (tokens);
}
