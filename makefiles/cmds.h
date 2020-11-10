#ifndef _CMD_H
#define _CMD_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int fun_cd(char** char_list);
int fun_pwd(char** char_list);
int fun_exit(char** char_list);
int fun_echo(char** char_list);
int fun_touch(char** char_list);
int fun_mkdir(char** char_list);
int fun_remove_dir(char** char_list);
#endif
