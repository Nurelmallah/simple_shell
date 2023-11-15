#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * create_env_buffer - creates a buffer for the new environment variable
 * @key: the key for the environment variable
 * @value: the value for the environment variable
 * Return: pointer to the new buffer
 */
char *create_env_buffer(const char *key, const char *value)
{
	size_t len = custom_strlen(key) + custom_strlen(value) + 2;
	char *buffer = malloc(len);

	if (buffer == NULL)
		exit(EXIT_FAILURE);

	custom_strcpy(buffer, key);
	custom_strcat(buffer, "=");

	if (value)
		custom_strcat(buffer, value);
	else
		custom_strcat(buffer, " ");

	return (buffer);
}

/**
 * set_environment - sets a new environment variable or updates an existing one
 * @args: pointer to an array of arguments
 * @program_name: name of the program for error printing
 * @input_count: count of user input for error printing
 * Return: 0 on success, -1 on failure
 */
int set_environment(char **args, char *program_name, int input_count)
{
	char *buffer;
	int i = get_index(args[1]);
	int n = sizeof(char *);
	size_t len1 = 0;
	(void)program_name, (void)input_count;

	if (args[1] && args[2] && args[3])
		return (-1);

	if (args[1] == NULL)
		return (print_environment(args, program_name, input_count));

	while (environ[len1])
		len1++;

	buffer = create_env_buffer(args[1], args[2]);

	if (i >= 0)
	{
		free(environ[i]);
		environ[i] = buffer;
	}
	else
	{
		free(environ[len1]);
		environ = custom_realloc(environ, (len1 + 1) * n, (len1 + 2) * n);
		environ[len1] = buffer;
		environ[len1 + 1] = NULL;
	}

	return (0);
}
