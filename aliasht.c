#include "main.h"
/**
* mimic_lias - mimics the alias builtin (man alias)
* @field: struct of arguments.
* Return: 0
*/
int mimic_lias(field_s *field)
{
	int i = 0;
	char *s = NULL;
	strlt_s *node = NULL;

	if (field->numofclarg == 1)
	{
		node = field->lias;
		while (node)
		{
			_givelias(node);
			node = node->linked;
		}
		return (0);
	}
	for (i = 1; field->cmdlinearg[i]; i++)
	{
		s = _strchr(field->cmdlinearg[i], '=');
		if (s)
			st_alis(field, field->cmdlinearg[i]);
		else
			_givelias(get_prefx(field->lias, field->cmdlinearg[i], '='));
	}

	return (0);
}
/**
* _nst_alis - get alias to string
* @field: parameter struct
* @s: alias string
*
* Return: Always 0 on success, 1 on error
*/
int _nst_alis(field_s *field, char *s)
{
	char *i, j;
	int kim;

	i = _strchr(s, '=');
	if (!i)
		return (1);
	j = *i;
	*i = 0;
	kim = delete_node_at_index(&(field->lias),
		get_at_index(field->lias, get_prefx(field->lias, s, -1)));
	*i = j;
	return (kim);
}
/**
* st_alis - sets alias to string
* @field: struct of arguments
* @s: the string alias
* Return: Always 0 on success, 1 on error
*/
int st_alis(field_s *field, char *s)
{
	char *kim;

	kim = _strchr(s, '=');
	if (!kim)
		return (1);
	if (!*++kim)
		return (_nst_alis(field, s));

	_nst_alis(field, s);

	return (add_node_to_end(&(info->alias), s, 0) == NULL);
}
/**
* _givelias - prints alias
* @node: alias node
* Return: 0
*/
int _givelias(strlt_s *node)
{
	char *kim = NULL, *s = NULL;

	if (node)
	{
		kim = _strchr(node->ring, '=');
		for (s = node->ring; s <= kim; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(kim + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
* disp_hist - show history as in shell
* @field: struct of arguments
* Return: 0
*/
int disp_hist(field_s *field)
{
	print_allist(field->cmdhist);
	return (0);
}
