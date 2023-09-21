#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
extern char **environ;
char *_strtok(char *str, const char *delim);
void change_dir(const char *token);
char *get_input(char *input);
void exec_comm(char *token);
/*int main(int argc, char* argv[], char* envp[]);*/
int main(void);
void semi_colon(char *input);
int _strlen(char *s);
char *trim_whitespace(char *str);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
typedef struct stringlist
{
	int no;
	char *ring;
	struct stringlist *linked;
} strlt_s;
typedef struct shellfields
{
	char *cmdarg;
	char **cmdlinearg;
	char *pathrdir;
	int numofclarg;
	unsigned int trcklcnt;
	int errornum;
	int flaglcnt;
	char filename;
	strl_s *envar;
	strl_s *cmdhist;
	strl_s *lias;
	char **environvar;
	int changein_env;
	int statinfo;
	char **commbuff;
	int tobuff;
	int rfiledes;
	int cntof_hist;
} field_s;
#define DEFAULT_FIELD {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
typedef struct shelbuilt
{
	char *form;
	int (*func)(field_s *);
} _inshell
#endif
