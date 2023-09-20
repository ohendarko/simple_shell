#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
/**
* main - main function
* @argc: -1 is command count
* @argv: imputted commands
* @envp: environment
* Return: return 0 on success
*/
int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	char *input = argv[1], *env_variable = envp[i], *token;
	size_t length;

	if (fgets(input, sizeof(input), stdin) == NULL)
		exit(EXIT_FAILURE);
	while (1)
	{
		if (argc < 2)
			exit(EXIT_FAILURE);
		length = _strlen(input);/*Remove the newline character from the input*/
		if (length > 0 && input[length - 1] == '\n')
			input[length - 1] = '\0';
		token = _strtok(input, " ");/*Split the input into command and arguments*/
		if (token == NULL)
			exit(EXIT_SUCCESS);/*Empty input, EXIT*/
		if (_strcmp(token, "exit") == 0)/*Check for exit command*/
			exit(EXIT_SUCCESS);
		if (_strcmp(token, "cd") == 0)/*Change directory implementation*/
		{
			token = _strtok(NULL, " ");
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
		while (env_variable != NULL)
		{
			printf("%s\n", env_variable);
			i++;
			env_variable = envp[i];
		}
	}
	return (0);
}
