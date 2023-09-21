#include "main.h"

/**
 * add_node_at_start - adds node to list start
 * @alpha: address
 * @s: str
 * @idx: index
 * Return: expected
 */
strlt_s *add_node_at_start(strlt_s **alpha, const char *s, int idx)
{
	strlt_s *fresh;

	if (!alpha)
		return (NULL);

	fresh = malloc(sizeof(strlt_s));
	if (!fresh)
		return (NULL);

	_memset((void *)fresh, 0, sizeof(strlt_s));
	fresh->idx = idx;

	if (s)
	{
		fresh->s = _strdup(s);
		if (!fresh->s)
		{
			free(fresh);
			return (NULL);
		}
	}

	fresh->linked = *alpha;
	*alpha = fresh;
	return (fresh);
}

/**
 * add_node_to_end - adds to end
 * @alpha: address of pointer to head node
 * @s: str field of node
 * @idx: index
 * Return: expeced
 */
strlt_s *add_node_to_end(strlt_s **alpha, const char *s, int idx)
{
	strlt_s *fresh, *node;

	if (!alpha)
		return (NULL);

	node = *alpha;
	fresh = malloc(sizeof(strlt_s));
	if (!new_node)
		return (NULL);

	_memset((void *)fresh, 0, sizeof(strlt_s));
	fresh->idx = idx;

	if (s)
	{
		fresh->s = _strdup(s);
		if (!fresh->s)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->linked)
			node = node->linked;
		node->linked = fresh;
	}
	else
		*alpha = fresh;

	return (fresh);
}

/**
 * print_elem_list - prints only the ring element
 * @h: pointer
 * Return: expected
 */
size_t print_elem_list(const strlt_s *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->ring ? h->ring : "(nil)");
		_puts("\n");
		h = h->linked;
		i++;
	}
	return (i);
}

/**
* delete_node_at_index - delete node at chosen index
* @head: address
* @index: node index
* Return: expected
*/
int delete_node_at_index(strlt_s **head, unsigned int index)
{
	strlt_s *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->linked;
		free(node->ring);
		free(node);
		return (1);
	}

	node = *head;

	while (node)
	{
		if (i == index)
		{
			prev_node->linked = node->linked;
			free(node->ring);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->linked;
	}
	return (0);
}

/**
* free_listt - frees all the nodes of a strlt_s list
* @head_ptr: address
* Return: void
*/
void free_listt(strlt_s **head_ptr)
{
	strlt_s *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->linked;
		free(node->ring);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}

