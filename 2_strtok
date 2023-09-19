#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
* _strtok - my strtok function
* @str: string to be tokenized
* @delim: delimiter
* Return: return what you have to
*/
char *_strtok(char *str, const char *delim)
{
	static char *current;
	char *start;

	if (current == NULL)
		current = NULL;

	if (str != NULL)
	{
		current = str;
	}
	while (*current != '\0' && strchr(delim, *current) != NULL)
		current++;
	if (*current == '\0')
	{
		return (NULL);
	}
	start = current;

	while (*current != '\0' && strchr(delim, *current) == NULL)
	{
		current++;
	}
	if (*current != '\0')
	{
		*current = '\0';
		current++;
	}
	return (start);
}
