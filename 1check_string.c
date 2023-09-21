#include "main.h"
/**
* strt_nt - converts a string to an integer
* @s: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int strt_nt(char *s)
{
	int i, gn = 1, fl = 0, utt;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && fl != 2; i++)
	{
		if (s[i] == '-')
			gn *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (gn == -1)
		utt = -res;
	else
		utt = res;

	return (utt);
}
/**
* check_deli - checks char s is delimiter
* @s: char to check
* @Delim: the delimiter string
* Return: 1 true, 0 false
*/
int check_deli(char s, char *Delim)
{
	while (*Delim)
		if (*Delim++ == s)
			return (1);
	return (0);
}
/**
* is_alpha - checks if alphabet
* @s: character to check
* Return: 1-s alphabet, 0
*/
int is_alpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}
