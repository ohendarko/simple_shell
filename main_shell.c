#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
/**
* main - main function
* Return: return 0 on success
*/
int main(void)
{
	char input[5000];
	char *token;
	size_t length;

	while (1)
	{
		fflush(stdout);/*Flush the output to ensure the prompt is displayed */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			exit(EXIT_FAILURE);
		}

		length = strlen(input);/*Remove the newline character from the input*/
		if (length > 0 && input[length - 1] == '\n')
		{
			input[length - 1] = '\0';
		}
		token = strtok(input, " ");/*Split the input into command and arguments*/

		if (token == NULL)
			continue;/*Empty input, prompt again*/
		if (strcmp(token, "exit") == 0)/*Check for exit command*/
			exit(0);
		if (strcmp(token, "cd") == 0)/*Change directory implementation*/
		{
			token = strtok(NULL, " ");
			if (token == NULL)
				chdir(getenv("HOME"));
			else
			{
				if (chdir(token) == -1)
					perror("-bash : cd");
			}
			continue;
		}
	exec_comm(token);/*Create and execute argument vector for execvp*/
	}
	return (0);
}
