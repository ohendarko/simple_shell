#include "main.h"

/**
 * start_struct - Initializes info_t struct
 * @field: Struct address
 */
void start_struct(field_s *field)
{
	field->cmdarg = NULL;
	field->cmdlinearg = NULL;
	field->pathrdir = NULL;
	field->numofclarg = 0;
}

/**
 * mk_struct - Initializes info_t struct
 * @field: Struct address
 * @av: Argument vector
 */
void mk_struct(field_s *field, char **av)
{
	int i = 0;

	field->filename = av[0];
	if (field->cmdarg)
	{
		field->cmdlinearg = _strtok(field->cmdarg, " \t");
		if (!field->cmdlinearg)
		{
			field->cmdlinearg = malloc(sizeof(char *) * 2);
			if (field->cmdlinearg)
			{
				field->cmdlinearg[0] = _strdup(field->cmdarg);
				field->cmdlinearg[1] = NULL;
			}
		}
		for (i = 0; field->cmdlinearg && field->cmdlinearg[i]; i++)
			;
		field->numofclarg = i;

		alout_alin(field);
		varout_varin(field);
	}
}

/**
 * struct_disslv - Frees info_t struct fields
 * @field: Struct address
 * @all: True if freeing all fields
 */
void struct_disslv(field_s *field, int all)
{
	f_free(field->cmdlinearg);
	field->cmdlinearg = NULL;
	field->pathrdir = NULL;
	if (all)
	{
		if (!field->commbuff)
			free(field->cmdarg);
		if (field->envar)
			free_listt(&(field->envar));
		if (field->cmdhist)
			free_list(&(field->cmdhist));
		if (field->lias)
			free_listt(&(field->lias));
		f_free(field->environvar);
		field->environvar = NULL;
		free_pointer((void **)field->commbuff);
		if (field->rfiledes > 2)
			close(field->rfiledes);
		_putchar(BUF_FLUSH);
	}
}

