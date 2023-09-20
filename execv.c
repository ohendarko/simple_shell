#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"
extern char **environ;
/**
* exec_comm - core shell function
* @token: argument passed
* Return: nothing
*/
void exec_comm(char *token)
{
	int argCount = 0;
	pid_t pid;
	char *args[5000];/*Adjust the size as needed*/;

	args[argCount++] = token;
	while ((token = _strtok(NULL, " ")) != NULL)
		args[argCount++] = token;
	args[argCount] = NULL;/*Null-terminate the argument vector*/
	pid = fork();/*Fork and execute the command*/
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)/*Child process*/
	{
		if (setenv("VAR_NAME", "VAR_VALUE", 1) == -1)
			exit(EXIT_FAILURE);
		if (execve(args[0], args, environ) < 0)
			exit(EXIT_FAILURE);
	}
	else/*Parent process*/
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
