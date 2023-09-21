#include "main.h"

/**
 * free_pointer - frees a pointer
 * @ptr: address to free
 * Return: expected
 */
int free_pointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

