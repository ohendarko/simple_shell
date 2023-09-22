#include "main.h"

/**
* ret_viron - returns the string array copy of our environ
* @field: struct of arguments
* Return: expected
*/
char **ret_viron(field_s *field)
{
	if (!field->environvar || field->changein_env)
	{
		field->environvar = get_liststr(field->envar);
		field->changein_env = 0;
	}

	return (field->environvar);
}

/**
* envar_out - Remove an env var
* @field: struct of args
* Return: 1 on delete, 0 otherwise
* @var: the string env var property
*/
int envar_out(field_s *field, char *var)
{
	strlt_s *node = field->envar;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = if_haystart(node->ring, var);
		if (p && *p == '=')
		{
			field->changein_env = delete_node_at_index(&(field->envar), i);
			i = 0;
			node = field->envar;
			continue;
		}
		node = node->linked;
		i++;
	}
	return (field->changein_env);
}

/**
 * envar_in - Initialize a new environment variable,
 *             or modify an existing one
 * @field: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int envar_in(field_s *field, char *var, char *value)
{
	char *buf = NULL;
	strlt_s *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = field->envar;
	while (node)
	{
		p = if_haystart(node->ring, var);
		if (p && *p == '=')
		{
			free(node->ring);
			node->ring = buf;
			field->changein_env = 1;
			return (0);
		}
		node = node->linked;
	}
	add_node_to_end(&(field->envar), buf, 0);
	free(buf);
	field->changein_env = 1;
	return (0);
}
