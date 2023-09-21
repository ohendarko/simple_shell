#include "main.h"

/**
* ret_viron - returns the string array copy of our environ
* @info: struct of arguments
* Return: expected
*/
char **ret_viron(field_s *field)
{
	if (!field->environvar || field->changein_env)
	{
		field->environvar = list_to_strings(info->env);
		field->changein_env = 0;
	}

	return (field->environvar);
}

/**
* envar_out - Remove an env var
* @info: struct of args
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
			field->changein_env = delete_node_at_index(&(field->envvar), i);
			i = 0;
			node = field->envvar;
			continue;
		}
		node = node->linked;
		i++;
	}
	return (info->env_changed);
}

/**
 * envar_in - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int envar_in(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

