#include "structs.h"
#include "macros.h"
#include "main.h"
/**
* _bash - core of main.
* @field: parameter
* @av: argument vector
* Return: 0
*/
int _bash(field_s *field, char **av)
{
	ssize_t i = 0;
	int inet = 0;

	while (i != -1 && inet != -2)
	{
		start_struct(field);/*pending*/
		if (check_shellmode(field))
			_puts("$ ");
		wrtchar_terr(BUF_FLUSH);/*pending*/
		i = read_line(field);
		if (i != -1)
		{
			mk_struct(field, av);
			inet = get_incomm(field);
			if (inet == -1)
				_getcmd(field);
		}
		else if (check_shellmode(field))/*pending*/
			_putchar('\n');
		struct_disslv(field, 0);
	}
	croap_fhist(field);
	struct_disslv(field, 1);
	if (check_shellmode(field) && field->statinfo)
		exit(field->statinfo);
	if (inet == -2)
	{
		if (field->errornum == -1)/*pending*/
			exit(field->statinfo);
		exit(field->errornum);
	}
	return (inet);
}

/**
* get_incomm - find builtin command
* @field: parameter
* Return: 0
*/
int get_incomm(field_s *field)
{
	int i, inet = -1;
	_inshell intble[] = {
		{"env", print_curenv},
		{"setenv", initnew_envvar},
		{"help", chan_d},
		{"alias", mimic_lias},
		{"history", disp_hist},
		{"unsetenv", rmenv_var},
		{"cd", change_dir},
		{"exit", exit_shell},
		{NULL, NULL}};

	for (i = 0; intble[i].form; i++)/*pending*/
		if (_strcmp(field->cmdlinearg[0], intble[i].form) == 0)
		{
			field->flaglcnt++;
			inet = intble[i].func(field);
			break;
		}
	return (inet);
}

/**
* _getcmd - find command in PATH
* @field: the parameter
* Return: void
*/
void _getcmd(field_s *field)
{
	char *pathrdir = NULL;
	int i, j;

	field->pathrdir = field->cmdlinearg[0];
	if (field->flaglcnt == 1)
	{
		field->trcklcnt++;
		field->flaglcnt = 0;
	}
	for (i = 0, j = 0; field->cmdarg[i]; i++)
		if (!check_deli(field->cmdarg[i], " \t\n"))
			j++;
	if (!j)
		return;
	pathrdir = find_inPATH(field, varof_envget(field, "PATH="),
			field->cmdlinearg[0]);
	if (pathrdir)
	{
		field->pathrdir = pathrdir;
		exec_comm(field);
	}
	else
	{
		if ((check_shellmode(field) || varof_envget(field, "PATH=")
			|| field->cmdlinearg[0][0] == '/') &&
				check_comm(field, field->cmdlinearg[0]))
			exec_comm(field);
		else if (*(field->cmdarg) != '\n')
		{
			field->statinfo = 127;
			err_msg(field, "not found\n");
		}
	}
}

/**
* exec_comm - forks a an exec thread to run cmd
* @field: the parameter & return info struct
* Return: void
*/
void exec_comm(field_s *field)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(field->pathrdir, field->cmdlinearg, ret_viron(field)) == -1)
		{
			struct_disslv(field, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(field->statinfo));
		if (WIFEXITED(field->statinfo))
		{
			field->statinfo = WEXITSTATUS(field->statinfo);
			if (field->statinfo == 126)
				err_msg(field, "Permission denied\n");
		}
	}
}
