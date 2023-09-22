#include "macros.h"
#include "main.h"
#include <stdio.h>
/**
* _strcat - concatenates 2 strings
* @dest: destination
* @src: source
* Return: return dest
*/
char *_strcat(char *dest, char *src)
{
	int deslen = 0;
	int srclen = 0;
	int i;

	for (i = 0; dest[i] != '\0'; i++)
	{
		deslen++;
	}
	for (i = 0; src[i] != '\0'; i++)
	{
		srclen++;
	}
	for (i = 0; i <= srclen; i++)
	{
		dest[deslen + i] = src[i];
	}
	return (dest);
}
