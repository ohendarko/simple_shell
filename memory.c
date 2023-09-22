#include "structs.h"
#include "macros.h"
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
/**
 * if_haystart - Ifstarts with haystack
 * @haystack: search
 * @needle: find
 * Return: 0
 */
char *if_haystart(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
