#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
/**
* main - main function
* argc: -1 is command count
* argv: imputted commands
* envp: environment
* Return: return 0 on success
*/
int main(void)
{
	char input[5000], *token/***env, *inputcp*/;
	size_t length;

	while (1)
	{
		if (fgets(input, sizeof(input), stdin) == NULL)
			exit(EXIT_FAILURE);
		length = _strlen(input);
		if (length > 0 && input[length - 1] == '\n')/*Rmv newline x'ter from input*/
			input[length - 1] = '\0';
		/*inputcp = strdup(input);
		semi_colon(inputcp);*handle ; operator*/
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
		/**
		*env = environ;
		*unsetenv("LS_COLORS");
		*printf("\nEnvironment:\n");
		*while (*env != NULL)
		*{
		*	printf("%s\n", *env);
		*	env++;
		*}
		*/
	}
	return (EXIT_SUCCESS);
}
