#ifndef STRUCTS_H
#define STRUCTS_H
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
typedef struct shelbuilt
{
	char *form;
	int (*func)(field_s *);
} _inshell;

#endif
