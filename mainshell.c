#include "macros.h"
#include "main.h"
/**
* main - main function
* @ac: argument count
* @av: argument vector
* Return: 0
*/
int main(int ac, char **av)
{
	field_s field[] = { DEFAULT_FIELD };
	int fd = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (fd)
	: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				pinput_str(av[0]);
				pinput_str(": 0: Can't open ");
				pinput_str(av[1]);
				wrtchar_terr('\n');
				wrtchar_terr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
	field->rfiledes = fd;
	}
	opu_envil(field);
	kan_fhist(field);
	_bash(field, av);
	return (EXIT_SUCCESS);
}
