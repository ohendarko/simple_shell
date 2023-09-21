#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2


#define USE_GETLINE 0
#define USE_STRTOK 0
 
#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096
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
int strt_nt(char *s);
int check_deli(char s, char *Delim);
int is_alpha(int s);
int mimic_lias(field_s *field);
int _nst_alis;
int st_alis(field_s *field, char *s);
int _givelias(strlt_s *node);
int disp_hist(field_s *field);
int change_dir(field_s *field);
int chan_d(field_s *field);
int exit_shell(field_s *field);
void rplc_hash(char *uff);
int cvstr_tint(char *s);
int pbase_ten(int inp, int fd);
char *atoi_clone(long int n, int b, int fl);
void err_msg(field_s *field, char *s);
size_t get_listlen(const strlt_s *h);
char **get_liststr(strlt_s *head);
size_t print_allist(const strlt_s *h);
strlt_s *get_prefx(strlt_s *node, char *prefix, char c);
ssize_t get_at_index(strlt_s *head, strlt_s *node);
ssize_t buff_ccoms(field_s *field, char **buff, size_t *len);
ssize_t read_line(field_s *field);
ssize_t get_buffer(field_s *field, char *buffer, size_t *i);
int next_fgets(field_s *field, char **ptr, size_t *length);
void block_xtrlc(__attribute__((unused)) int sig_num);
int print_curenv(field_s *field);
char *varof_envget(field_s *field, const char *n);
int initnew_envvar(field_s *field);
int rmenv_var(field_s *field);
int opu_envil(field_s *field);
int prinp_str(char *s, int fd);
void pinput_str(char *s);
int wrtchar_terr(char s);
int wrtchat_tfd(char s, int fd);
strlt_s *add_node_at_start(strlt_s **alpha, const char *s, int idx);
strlt_s *add_node_to_end(strlt_s **alpha, const char *s, int idx);
size_t print_elem_list(const strlt_s *h);
int delete_node_at_index(strlt_s **head, unsigned int index);
void free_listt(strlt_s **head_ptr);
int _bash(field_s *field, char **av);
int get_incomm(field_s *field);
void exec_comm(field_s *field);
int free_pointer(void **ptr);
char **ret_viron(field_s *field);


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
} _inshell
#endif
