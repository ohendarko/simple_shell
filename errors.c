#include "shell.h"

/**
 * pinput_str - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void pinput_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		wrtchar_terr(str[i]);
		i++;
	}
}

/**
 * wrtchar_terr - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int wrtchar_terr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * wrtchat_tfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int wrtchat_tfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * prinp_str - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int prinp_str(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += wrtchat_tfd(*str++, fd);
	}
	return (i);
}

