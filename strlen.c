#include "macros.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
/**
* _strlen - returns length of s
* @s: pointer to swap
* Return: return 0
*/
int _strlen(char *s)
{
	int len = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		len++;
	} return (len);
}
