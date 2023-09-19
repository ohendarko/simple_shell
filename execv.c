#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

/*Change directory implementation*/
void exec_comm(char *token)
{
	char *args[20];/*Adjust the size as needed*/
	int argCount;
	pid_t pid;
 
	args[0] = token;
	argCount = 1;
	while ((token = _strtok(NULL, " ")) != NULL)
	{
		args[argCount++] = token;
	}
	args[argCount] = NULL;/*Null-terminate the argument vector*/
	
	pid = fork();/*Fork and execute the command*/

	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)/*Child process*/
	{
		if (execvp(args[0], args) < 0)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else/*Parent process*/
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
