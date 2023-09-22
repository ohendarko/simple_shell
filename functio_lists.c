#include "structs.h"
#include "macros.h"
#include "main.h"

/**
* get_listlen - find length of list
* @h: pointer
* Return: expected
*/
size_t get_listlen(const strlt_s *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->linked;
		i++;
	}
	return (i);
}

/**
* get_liststr - Output is  a string array
* @head: address of first node
* Return: expected
*/
char **get_liststr(strlt_s *head)
{
	strlt_s *node = head;
	size_t i = get_listlen(head), j;
	char **strs;
	char *ring;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->linked, i++)
	{
		ring = malloc(_strlen(node->ring) + 1);
		if (!ring)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		ring = _strcpy(ring, node->ring);
		strs[i] = ring;
	}
	strs[i] = NULL;
	return (strs);
}

/**
* print_allist - prints all elements
* @h: Adress to first node
* Return: expected
*/
size_t print_allist(const strlt_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(atoi_clone(h->no, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->ring ? h->ring : "(nil)");
		_puts("\n");
		h = h->linked;
		i++;
	}
	return (i);
}

/**
* get_prefx - returns node with prefix
* @node: pointer
* @prefix: string
* @c: next x'ter
* Return: expected
*/
strlt_s *get_prefx(strlt_s *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = if_haystart(node->ring, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->linked;
	}
	return (NULL);
}

/**
* get_at_index - gets the index of a node
* @head: pointer
* @node: another pointer
* Return: expected
*/
ssize_t get_at_index(strlt_s *head, strlt_s *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->linked;
		i++;
	}
	return (-1);
}
