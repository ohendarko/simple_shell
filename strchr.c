#include "main.h"
#include <stdio.h>
/**
* _strchr - set b to n bytes of s
* @s: bytes location
* @c: constant byte
* n: number of bytes
* Return: return s
*/
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (*s == c)
	{
		return (s);
	}
	return (NULL);
}
