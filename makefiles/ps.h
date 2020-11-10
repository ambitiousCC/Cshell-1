#ifndef _PS_H
#define _PS_H
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#define MAX_LEN 20
typedef struct ps_info
{
    char pname[MAX_LEN];
    char user[MAX_LEN];
    int  pid;
    int  ppid;
    char state;
    struct ps_info *next;
}mps;
void record_pwd();
void cd_pwd();
mps *trav_dir(char *dir);
int read_info(char d_name[],struct ps_info *p1);
int fun_ps(char** char_list);
void uid_to_name(uid_t uid, struct ps_info *p1);
int is_num(char p_name[]);
void print_ps(struct ps_info *head);
struct ps_info *trav_dir(char dir[]);
int bufsize = 1024;
char *buffer_pwd;
#endif
