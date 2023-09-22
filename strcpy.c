#include "structs.h"
#include "macros.h"
#include "main.h"
#include <stdio.h>
/**
* _strcpy - entry point
* @dest: parameter to be printed
* @src: parameter
* Return: return dest
*/
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
