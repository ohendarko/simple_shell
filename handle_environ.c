#include "main.h"
/**
* print_curenv - prints current env
* @field: struct of arguments.
* Return: 0
*/
int print_curenv(field_s *field)
{
	print_elem_list(field->envar);
	return (0);
}

/**
* varof_envget - get value of an env var
* @field: structure of arguments
* @n: passed argument
* Return: expected
*/
char *varof_envget(field_s *field, const char *n)
{
	strlt_s *node = field->envar;
	char *s;

	while (node)
	{
		s = if_haystart(node->str, n);
		if (s && *s)
			return (s);
		node = node->linked;
	}
	return (NULL);
}

/**
* initnew_envvar - Initialize new env var
* @field: struct of arguments
* Return: 0
*/
int initnew_envvar(field_s *field)
{
	if (field->numofclarg != 3)
	{
		pinput_str("Incorrect number of arguments\n");
		return (1);
	}
	if (envar_in(field, field->cmdlinearg[1], field->cmdlinearg[2]))
		return (0);
	return (1);
}

/**
* rmenv_var - remove env var
* @field: struct of arguments
* Return: 0
*/
int rmenv_var(field_s *field)
{
	int i;

	if (field->numofclarg == 1)
	{
		pinput_str("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= field->numofclarg; i++)
		envar_out(field, field->cmdlinearg[i]);

	return (0);
}

/**
* opu_envil - populates env linked list
* @field: struct of arguments
* Return: 0
*/
int opu_envil(field_s *field)
{
	strlt_s *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_to_end(&node, environ[i], 0);
	field->envar = node;
	return (0);
}
