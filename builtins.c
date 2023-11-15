#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * exit_shell - exits the shell
 * @args: pointer to array of arguments
 * @program_name: name of the program for error printing
 * @input_count: count of user input for error printing
 * Return: 2 if exit receives an invalid argument
 */
int exit_shell(char **args, char *program_name, int input_count)
{
	int num = 0, i = 0;
	(void) program_name, (void) input_count;

	if (args == NULL || args[1] == NULL)
		exit(0);

	while (args[1][i])
	{
		if (!(args[1][i] >= '0' && args[1][i] <= '9'))
			break;
		num *= 10;
		num += args[1][i] - '0';
		i++;
	}

	if (args[1][i] == '\0')
		exit(num);

	print_error("%s: %d: exit: Illegal number: %s\n",
		program_name, input_count, args[1]);
	return (2);
}

/**
 * print_environment - prints environment key-value pairs
 * @args: pointer to array of arguments
 * @program_name: name of the program for error printing
 * @input_count: count of user input for error printing
 * Return: 0 on success, 1 otherwise
 */
int print_environment(char **args, char *program_name, int input_count)
{
	size_t i = 0;
	(void) program_name, (void) input_count;

	if (args == NULL || args[0] == NULL)
		exit(EXIT_FAILURE);

	for (; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], custom_strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * unset_environment - removes a variable from the user environment
 * @args: pointer to array of arguments
 * @program_name: name of the program for error printing
 * @input_count: count of user input for error printing
 * Return: -1 if the variable is not found, 0 on success
 */
int unset_environment(char **args, char *program_name, int input_count)
{
	int i = get_index(args[1]);
	(void) program_name, (void) input_count;

	if (args == NULL || args[1] == NULL || i == -1 || !custom_strlen(args[1]))
		return (-1);

	free(environ[i]);

	while (environ[i])
	{
		environ[i] = environ[i + 1];
		i++;
	}

	return (0);
}

/**
 * change_directory - changes the current directory
 * @args: pointer to array of arguments
 * @program_name: name of the program for error printing
 * @input_count: count of user input for error printing
 * Return: 0 on success, 2 on error
 */
int change_directory(char **args, char *program_name, int input_count)
{
	if (args[1] == NULL)
	{
		change_pwd("OLDPWD", program_name, input_count);
		chdir(_getenv("HOME"));
	}
	else if (custom_strcmp(args[1], "-") == 0)
	{
		chdir(_getenv("OLDPWD"));
		change_oldpwd(program_name, input_count);
	}
	else
	{
		change_oldpwd(program_name, input_count);

		if (chdir(args[1]) == -1)
		{
			print_error("%s: %d: cd: can't cd to %s\n",
				program_name, input_count, args[1]);
			return (2);
		}
	}

	change_pwd("PWD", program_name, input_count);
	return (0);
}
