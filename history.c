#include "shell.h"

/**
 * filhist_obt - Gets the history file
 * @info: Parameter struct
 *
 * Return: Allocated string containing history file
 */
char *filhist_obt(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * croap_fhist - Creates a file or appends to an existing file
 * @info: Parameter struct
 *
 * Return: 1 on success, else -1
 */
int croap_fhist(info_t *info)
{
	ssize_t fd;
	char *filename = filhist_obt(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
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
 * @info: Parameter struct
 *
 * Return: Histcount on success, 0 otherwise
 */
int kan_fhist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = filhist_obt(info);

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
			addto_lkhist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		addto_lkhist(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	new_numof_hist(info);
	return (info->histcount);
}

/**
 * addto_lkhist - Adds entry to a history linked list
 * @info: Parameter struct
 * @buf: Buffer
 * @linecount: The history linecount, histcount
 *
 * Return: Always 0
 */
int addto_lkhist(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * new_numof_hist - Renumbers the history linked list after changes
 * @info: Parameter struct
 *
 * Return: The new histcount
 */
int new_numof_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

