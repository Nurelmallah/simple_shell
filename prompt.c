#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * get_prompt - prompt for custom shell
 */
void get_prompt(void)
{
	int index, length, i;
	char full_prompt[1024];
	char abbreviated_prompt[1024];

	getcwd(full_prompt, sizeof(full_prompt));

	for (i = 0, index = 0; full_prompt[i] != '\0'; ++i)
		if (full_prompt[i] == '/')
			index = i;

	length = i;
	abbreviated_prompt[0] = '~';

	for (i = 1; index < length; ++i)
	{
		abbreviated_prompt[i] = full_prompt[index++];
	}

	abbreviated_prompt[i++] = '$';
	abbreviated_prompt[i++] = ' ';
	abbreviated_prompt[i] = '\0';

	write(STDOUT_FILENO, abbreviated_prompt, i);
}
