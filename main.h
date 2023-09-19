#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
char *_strtok(char *str, const char *delim);
void change_dir(const char *token);
char *get_input(char *input);
void exec_comm(char *token);

#endif
