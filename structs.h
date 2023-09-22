#ifndef STRUCTS_H
#define STRUCTS_H
#include "main.h"
#include "macros.h"
/**
* struct stringlist - singly-linked list
* @no: the number field
* @ring: string element
* @linked: adress to next node
*/
typedef struct stringlist
{
	int no;
	char *ring;
	struct stringlist *linked;
} strlt_s;
/**
*struct passinfo - pseudo-arguements
*@cmdarg: generated from getline arguments
*@cmdlinearg: array of strings
*@pathrdir: string path
*@numofclarg: argument count
*@trcklcnt: error count
*@errornum: exit() error code
*@flaglcnt: count line
*@filename: program filename
*@envar: local copy environ
*@environvar: custom mod copy of environ
*@cmdhist: history
*@lias: alias
*@changein_env: environ change
*@statinfo: return status
*@commbuff: address
*@tobuff: CMD_type ||, &&, ;
*@rfiledes: file des to read line input from
*@cntof_hist: history count
*/
typedef struct shellfields
{
	char *cmdarg;
	char **cmdlinearg;
	char *pathrdir;
	int numofclarg;
	unsigned int trcklcnt;
	int errornum;
	int flaglcnt;
	char *filename;
	strlt_s *envar;
	strlt_s *cmdhist;
	strlt_s *lias;
	char **environvar;
	int changein_env;
	int statinfo;
	char **commbuff;
	int tobuff;
	int rfiledes;
	int cntof_hist;
} field_s;
#define DEFAULT_FIELD {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}
/**
*struct shelbuilt - builtin str and related f'tion
*@type: commanz eflag
*@func: betty> function
*/
typedef struct shelbuilt
{
	char *form;
	int (*func)(field_s *);
} _inshell;

#endif
