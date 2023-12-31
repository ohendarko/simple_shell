#include "macros.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
/**
* _strncpy - concatenates 2 strings
* @dest: destination
* @src: source
* @n: bytes
* Return: return dest
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
