#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @field: the parameter struct
 * @buf: the char buffer
 * @cp: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(field_s *field, char *buf, size_t *cp)
{
	size_t j = *cp;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		field->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		field->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		field->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*cp = j;
	return (1);
}

/**
 * if_xont - checks if we should continue chaining based on last status
 * @field: the parameter struct
 * @buf: the char buffer
 * @cp: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void if_xont(field_s *field, char *buf, size_t *cp, size_t i, size_t len)
{
	size_t j = *cp;

	if (field->cmd_buf_type == CMD_AND)
	{
		if (field->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (field->cmd_buf_type == CMD_OR)
	{
		if (!field->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*cp = j;
}

/**
 * alout_alin - replaces an aliases in the tokenized string
 * @field: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alout_alin(field_s *field)
{
	int i;
	list_t *node;
	char *cp;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(field->alias, field->argv[0], '=');
		if (!node)
			return (0);
		free(field->argv[0]);
		cp = _strchr(node->str, '=');
		if (!cp)
			return (0);
		cp = _strdup(cp + 1);
		if (!cp)
			return (0);
		field->argv[0] = cp;
	}
	return (1);
}

/**
 * varout_varin - replaces vars in the tokenized string
 * @field: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int varout_varin(field_s *field)
{
	int i = 0;
	list_t *node;

	for (i = 0; field->argv[i]; i++)
	{
		if (field->argv[i][0] != '$' || !field->argv[i][1])
			continue;

		if (!_strcmp(field->argv[i], "$?"))
		{
			replace_string(&(field->argv[i]),
						   _strdup(convert_number(field->status, 10, 0)));
			continue;
		}
		if (!_strcmp(field->argv[i], "$$"))
		{
			replace_string(&(field->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(field->env, &field->argv[i][1], '=');
		if (node)
		{
			replace_string(&(field->argv[i]),
						   _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&field->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * strout_strin - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int strout_strin(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

