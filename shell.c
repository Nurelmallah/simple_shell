#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define READ_BUF_SIZE 1024

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
	ssize_t read_result;

	while (1)
	{
		display_prompt();

		read_result = read_buf(input, &input_length);

		if (read_result == -1)
		{
			printf("\n");
			break;
		}

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

/**
 * read_buf - Reads characters into a buffer.
 * @buf: The buffer to store the characters.
 * @len: Pointer to the length of the buffer.
 *
 * Return: The number of characters read
 * (excluding the null-terminator), or -1 on failure.
 */
ssize_t read_buf(char *buf, size_t *len)
{
	static char read_buffer[READ_BUF_SIZE];
	static ssize_t index;
	ssize_t bytes_read = 0;

	if (index == 0)
	{
		bytes_read = read(STDIN_FILENO, read_buffer, READ_BUF_SIZE);

		if (bytes_read <= 0)
		{
			return (-1);
		}
	}

	if (index < bytes_read)
	{
		*len = bytes_read - index;
		memcpy(buf, read_buffer + index, *len);
		index += *len;
		return (*len);
	}
	else
	{
		index = 0;
		return (read_buf(buf, len));
	}
}

