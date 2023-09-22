#include "main.h"

/**
 * filhist_obt - Gets the history file
 * @field: Parameter struct
 *
 * Return: Allocated string containing history file
 */
char *filhist_obt(field_s *field)
{
	char *buff, *dir;

	dir = _getenv(field, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buf[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * croap_fhist - Creates a file or appends to an existing file
 * @field: Parameter struct
 *
 * Return: 1 on success, else -1
 */
int croap_fhist(field_s *field)
{
	ssize_t fd;
	char *filename = filhist_obt(field);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = field->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * kan_fhist - Reads history from file
 * @field: Parameter struct
 *
 * Return: Histcount on success, 0 otherwise
 */
int kan_fhist(field_s *field)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = filhist_obt(field);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			addto_lkhist(field, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		addto_lkhist(field, buf + last, linecount++);
	free(buf);
	field->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(field->history), 0);
	new_numof_hist(field);
	return (field->histcount);
}

/**
 * addto_lkhist - Adds entry to a history linked list
 * @field: Parameter struct
 * @buf: Buffer
 * @linecount: The history linecount, histcount
 *
 * Return: Always 0
 */
int addto_lkhist(field_s *field, char *buf, int linecount)
{
	list_t *node = NULL;

	if (field->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!field->history)
		field->history = node;
	return (0);
}

/**
 * new_numof_hist - Renumbers the history linked list after changes
 * @field: Parameter struct
 *
 * Return: The new histcount
 */
int new_numof_hist(field_s *field)
{
	list_t *node = field->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (field->histcount = i);
}

