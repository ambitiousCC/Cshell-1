#ifndef _LS_H
#define _LS_H
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
char *get_mode(mode_t m, char *str);
int _time(int year);
void time_ch(time_t num);
int fun_ls(char** char_list);
#endif
