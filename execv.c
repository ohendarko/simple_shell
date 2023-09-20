#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
/**
* exec_comm - core shell function
* @token: argument passed
* Return: nothing
*/
void exec_comm(char *token)
{
	char *args[1024], command[1024];/*Adjust the size as needed*/
	int argCount = 0;
	FILE *pipe;
	pid_t pid;

	if (strcmp(token, "/bin/sh") == 0) /*Check if the token is "/bin/sh"*/
	{
		printf("Enter a command: ");
		fflush(stdout);
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}

		pipe = popen(token, "w");/*Open a pipe to the /bin/sh shell*/

		if (pipe == NULL)
		{
			perror("popen");
			exit(EXIT_FAILURE);
		}

		fprintf(pipe, "%s", command);/*Send the command to the shell*/
		fflush(pipe);
		pclose(pipe);/*Close the pipe*/
	}
	else
	{
		args[argCount++] = token;/*If it's not /bin/sh,treat as regular command*/
		while ((token = strtok(NULL, " ")) != NULL)
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
}
