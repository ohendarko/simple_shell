#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
/*Change directory implementation*/
char *get_input(char *input)
{
	if (fgets(input, sizeof(input), stdin) == NULL)
	{
		perror("Error reading input");
		exit(EXIT_FAILURE);
	}
 /*Remove the newline character from the input*/
	size_t length = strlen(input);

	if (length > 0 && input[length - 1] == '\n')
	{
		input[length - 1] = '\0';
	}
	return (input);
}
