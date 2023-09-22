#include "main.h"
/**
* prinp_str - Prints input
* @s: string
* @fd: File Descriptor
* Return: betty
*/
int prinp_str(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += wrtchat_tfd(*s++, fd);
	}
	return (i);
}
/**
* pinput_str - print input string
* @s: string
* Return: void
*/
void pinput_str(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		wrtchar_terr(s[i]);
		i++;
	}
}
/**
* wrtchar_terr - write to stderr
* @s: character
* Return: 0
*/
int wrtchar_terr(char s)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (s != BUF_FLUSH)
		buffer[i++] = s;
	return (1);
}

/**
* wrtchat_tfd - Write to given file desc.
* @s: Character
* @fd: File Descriptor
* Return: betty
*/
int wrtchat_tfd(char s, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (s != BUF_FLUSH)
		buf[i++] = s;
	return (1);
}
