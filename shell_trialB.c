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
	char input[100];
	char *token;

	while (1)
	{
		printf("$ ");
		fflush(stdout);/*Flush the output to ensure the prompt is displayed */
		get_input(input);
/*Split the input into command and arguments*/

		token = _strtok(input, " ");

		if (token == NULL)
		{
			continue;/*Empty input, prompt again*/
		}
		if (strcmp(token, "exit") == 0)/*Check for exit command*/
			exit(0);
		if (strcmp(token, "cd") == 0)/*Change directory implementation*/
		{
			token = _strtok(NULL, " ");
			if (token == NULL)
			{
				chdir(getenv("HOME"));
			}
			else
			{
				if (chdir(token) == -1)
				{
					perror("-bash : cd");
				}
			}
			continue;
		}
	exec_comm(token);/*Create and execute argument vector for execvp*/
	}
	return (0);
}
