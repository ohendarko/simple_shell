#include "main.h"
#include "structs.h"
#include "macros.h"
/**
* change_dir - changes current directory
* @field: struct of arguments
* Return: 0
*/
int change_dir(field_s *field)
{
	char *s, *dir, buff[1024];
	int cdret;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!field->cmdlinearg[1])
	{
		dir = varof_envget(field, "HOME=");
		if (!dir)
			cdret = chdir((dir = varof_envget(field, "PWD=")) ? dir : "/");
		else
			cdret = chdir(dir);
	}
	else if (_strcmp(field->cmdlinearg[1], "-") == 0)
	{
		if (!varof_envget(field, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(varof_envget(field, "OLDPWD=")), _putchar('\n');
		cdret = chdir((dir = varof_envget(field, "OLDPWD=")) ? dir : "/");
	}
	else
		cdret = chdir(field->cmdlinearg[1]);
	if (cdret == -1)/*pending*/
	{
		err_msg(field, "can't cd to ");
		pinput_str(field->cmdlinearg[1]), wrtchar_terr('\n');
	}
	else
	{
		envar_in(field, "OLDPWD", varof_envget(field, "PWD="));
		envar_in(field, "PWD", getcwd(buff, 1024));
	}
	return (0);
}
/**
* chan_d - Changes process current directory
* @field: struct of arguments
* Return: 0
*/
int chan_d(field_s *field)
{
	char **rarg;

	/*pending*/
	rarg = field->cmdlinearg;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*rarg);
	return (0);/*pending*/
}
/**
* exit_shell - exit shell
* @field: struct containing args.
* Return: 0
*/
int exit_shell(field_s *field)
{
	int checex;

	if (field->cmdlinearg[1])
	{
		checex = cvstr_tint(field->cmdlinearg[1]);
		if (checex == -1)/*pending*/
		{
			field->statinfo = 2;
			err_msg(field, "Illegal number: ");
			pinput_str(field->cmdlinearg[1]);
			wrtchar_terr('\n');/*pending*/
			return (1);
		}
		field->errornum = cvstr_tint(field->cmdlinearg[1]);
		return (-2);
	}
	field->errornum = -1;
	return (-2);
}
