#include "main.h"
#include <ctype.h>
/**
* trim_whitespace - Trim leading and trailing whitespace frm string.
* @str: input string to trim
*
* Return: pointer to the trimmed string
*/
char *trim_whitespace(char *str)
{
	char *end, *start = str, *result;
	size_t trimmed_len;

	while (isspace(*start))/*Trim leading whitespace*/
		start++;
	if (*start == '\0')
	{
		result = malloc(1);
		if (result == NULL)
			exit(EXIT_FAILURE);
		result[0] = '\0';
		return (result);
	}
	end = str + _strlen(str) - 1;/*Trim trailing whitespace*/
	while (end > start && isspace(*end))
		end--;
	trimmed_len = end - start + 1;
	result = malloc(trimmed_len + 1);
	if (result == NULL)
		exit(EXIT_FAILURE);
	_strncpy(result, start, trimmed_len);
	result[trimmed_len] = '\0';
	return (result);
}
/**
* semi_colon - handles semicolon operator
* @input: argument passed
*
* Return: betty
*/
void semi_colon(char *input)
{
	char *token2, *command;
	char *args[5000];
	int argCount = 0, i;

	token2 = _strtok(input, ";");
	while (token2 != NULL)
	{
		command = trim_whitespace(token2);

		if (_strlen(command) > 0)
			args[argCount++] = command;
		token2 = _strtok(NULL, ";");
	}
	args[argCount] = NULL;
	for (i = 0; i < argCount; i++)
	{
		if (_strcmp(args[i], "") != 0)
			exec_comm(args[i]);
	}
}
