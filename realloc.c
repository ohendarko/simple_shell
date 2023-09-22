#include "structs.h"
#include "macros.h"
#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @byte: the byte to fill *s with
 * @num: the amount of bytes to be filled
 * Return: a pointer to the memory area s
 */
char *_memset(char *s, char byte, unsigned int num)
{
	char *ptr = s;

	while (num--)
		*ptr++ = byte;

	return (s);
}

/**
 * f_free - frees a string of strings
 * @pp: string of strings
 */
void f_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * re_alloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to the reallocated block
 */
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);

	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}

