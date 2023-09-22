#include "main.h"
#include "macros.h"
/**
* rplc_hash - Replaces 1st instance of '#' with '\0'
* @uff: Address
* Return: 0
*/
void rplc_hash(char *uff)
{
	int i;

	for (i = 0; uff[i] != '\0'; i++)
		if (uff[i] == '#' && (!i || uff[i - 1] == ' '))
		{
			uff[i] = '\0';
			break;
		}
}
/**
* cvstr_tint - converts str to int
* @s: str
* Return: 0
*/
int cvstr_tint(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')/*pending*/
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else/*PENDING*/
			return (-1);
	}
	return (res);
}

/**
* pbase_ten - Prints a decimal(base ten)
* @inp: input
* @fd: File Descriptor
* Return: expected
*/
int pbase_ten(int inp, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, cnt = 0;
	unsigned int cab, curr;

	if (fd == STDERR_FILENO)
		__putchar = wrtchar_terr;
	if (inp < 0)
	{
		cab = -inp;
		__putchar('-');
		cnt++;
	}
	else
		cab = inp;
	curr = cab;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (cab / i)
		{
			__putchar('0' + curr / i);
			cnt++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	cnt++;

	return (cnt);
}

/**
* atoi_clone - clone of atoi
* @n: number
* @b: base
* @fl: argument flags
* Return: expected
*/
char *atoi_clone(long int n, int b, int fl)
{
	static char *arr;
	static char buff[50];
	char sn = 0, *p;
	unsigned long i = n;

	if (!(fl & CONVERT_UNSIGNED) && n < 0)
	{
		i = -n;
		sn = '-';
	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';

	do {
		*--p = arr[i % b];
		i /= b;
	} while (i != 0);

	if (sn)
		*--p = sn;
	return (p);
}
/**
* err_msg - prints error msg
* @field: parameter
* @s: string
* Return: 0
*/
void err_msg(field_s *field, char *s)
{
	pinput_str(field->filename);
	pinput_str(": ");
	pbase_ten(field->trcklcnt, STDERR_FILENO);
	pinput_str(": ");
	pinput_str(field->cmdlinearg[0]);
	pinput_str(": ");
	pinput_str(s);
}
