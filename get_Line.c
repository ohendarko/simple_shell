#include "main.h"

/**
* buff_ccoms - buffer chained commands
* @field: struct of arguments
* @buff: address
* @len: another address
* Return: expected
*/
ssize_t buff_ccoms(field_s *field, char **buff, size_t *len)
{
	ssize_t i = 0;
	size_t meno = 0;

	if (!*len) /*PENDING*/
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, block_xtrlc);
#if USE_GETLINE
		i = getline(buff, &meno, stdin);
#else
		i = next_fgets(info, buff, &meno);
#endif
		if (i > 0)/*PENDING*/
		{
			if ((*buff)[i - 1] == '\n')
			{
				(*buff)[i - 1] = '\0';/*PENDING*/
				i--;
			}
			field->flaglcnt = 1;
			rplc_hash(*buff);
			addto_lkhist(field, *buff, field->cntof_hist++);
			{
				*len = i;
				field->commbuff = buff;
			}
		}
	}
	return (i);
}

/**
* read_line - get what's on the line
* @field: struct of arguments
* Return: expected
*/
ssize_t read_line(field_s *field)
{
	static char *buff; /*PENDING semicolon*/
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buff_ccoms(field, &buff, &len);
	if (r == -1) /*PENDING*/
		return (-1);
	if (len) /*PENDING*/
	{
		j = i;
		p = buff + i;

		if_xont(field, buff, &j, i, len);
		while (j < len) /*PENDING*/
		{
			if (checkif_cdeli(info, buff, &j))
				break;
			j++;
		}

		i = j + 1; /*PENDING*/
		if (i >= len)
		{
			i = len = 0; /*PENDING*/
			field->tobuffe = CMD_NORM;
		}

		*buf_p = p; /*PENDING*/
		return (_strlen(p));
	}

	*buf_p = buff; /*PENDING*/
	return (r);
}

/**
 * get_buffer - read buffer
 * @field: struct of arguments
 * @buffer: buffer
 * @i: size
 * Return: expected
 */
ssize_t get_buffer(field_s *field, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(field->rfiledes, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * next_fgets - get nextline from STDIN
 * @field: struct of arguments
 * @ptr: address
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int next_fgets(field_s *field, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = get_buffer(field, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = re_alloc(p, s, s ? s + k : k + 1);
	if (!new_p) /*pending*/
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * block_xtrlc - block ^C
 * @sig_num: the signal number
 * Return: Void
 */
void block_xtrlc(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

