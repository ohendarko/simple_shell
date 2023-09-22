#include "macros.h"
#include "main.h"

/**
 * checkif_cdeli - test if chain delimiter
 * @field: struct of args
 * @buf: the char buffer
 * @cp: address of current position in buf
 * Return: 1 if chain delimiter, 0 otherwise
 */
int checkif_cdeli(field_s *field, char *buf, size_t *cp)
{
	size_t j = *cp;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		field->tobuff = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		field->tobuff = CMD_AND;
	}
	else if (buf[j] == ';') /*PENDING*/
	{
		buf[j] = 0;
		field->tobuff = CMD_CHAIN;
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

	if (field->tobuff == CMD_AND)
	{
		if (field->statinfo)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (field->tobuff == CMD_OR)
	{
		if (!field->statinfo)/*pending*/
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
	strlt_s *node;
	char *cp;

	for (i = 0; i < 10; i++)
	{
		node = get_prefx(field->lias, field->cmdlinearg[0], '=');
		if (!node)
			return (0);
		free(field->cmdlinearg[0]);
		cp = _strchr(node->ring, '=');
		if (!cp)
			return (0);
		cp = _strdup(cp + 1);
		if (!cp)
			return (0);
		field->cmdlinearg[0] = cp;
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
	strlt_s *node;

	for (i = 0; field->cmdlinearg[i]; i++)
	{
		if (field->cmdlinearg[i][0] != '$' || !field->cmdlinearg[i][1])
			continue;

		if (!_strcmp(field->cmdlinearg[i], "$?"))
		{
			strout_strin(&(field->cmdlinearg[i]),
						   _strdup(atoi_clone(field->statinfo, 10, 0)));
			continue;
		}
		if (!_strcmp(field->cmdlinearg[i], "$$"))
		{
			strout_strin(&(field->cmdlinearg[i]),
						   _strdup(atoi_clone(getpid(), 10, 0)));
			continue;
		}
		node = get_prefx(field->envar, &field->cmdlinearg[i][1], '=');
		if (node)
		{
			strout_strin(&(field->cmdlinearg[i]),
						   _strdup(_strchr(node->ring, '=') + 1));
			continue;
		}
		strout_strin(&field->cmdlinearg[i], _strdup(""));
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

