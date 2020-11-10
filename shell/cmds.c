#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cmds.h"

int fun_cd(char** char_list){
    if(char_list[1] == NULL){
        printf("Please enter the correct directory\n");
    }else{
        if(chdir(char_list[1]) != 0){
            perror("myshell");
        }
    }
    return 1;
}

int fun_pwd(char** char_list){
    int bufsize = 1024;
    char *buffer = malloc(sizeof(char)*bufsize);
    if (!buffer){
        printf("allocation error1\n");
        exit(1);
    }
    while (1){
        if(getcwd(buffer, bufsize) == NULL){
            bufsize += bufsize;
            buffer = realloc(buffer, sizeof(char)*bufsize);
            if (!buffer){
                printf("allocation error2\n");
                exit(1);
                }
        }else{
            printf("current working directory : %s\n", buffer);
            free(buffer);
            return 1;
        }
    }
}


int fun_exit(char** char_list){

    printf("------------------------------goodbye-----------------------------\n");
    return 0;
}

int fun_echo(char** char_list){
    int i;
    if (char_list[1] == NULL){
        printf("Enter correct output.\n");
    }else{
        for ( i = 1; char_list[i] != NULL; i++)
        {
            printf("%s ", char_list[i] );
        }
        printf("\n");
    }
    return 1;
}

int fun_touch(char** char_list){
    FILE *file = NULL;

    file=fopen(char_list[1],"w");
    fclose(file);
    return 1;
}
int fun_mkdir(char** char_list){
    if(mkdir(char_list[1],0770)!=0) //数字代表含义，按位置：（文件所有者，用户组，其他用户）；1.可执行； 2.可读； 4.可读可写； 7可读可写可执行
    perror("mkdir"),exit(-1);

    printf("mkdir directory  success .\n");
    return 1;
}
int fun_remove_dir(char** char_list)
{
    if (char_list[1] == NULL){
        printf("Enter correct dir_name.\n");
    }else{
    const char *dir = char_list[1];
    char cur_dir[] = ".";
    char up_dir[] = "..";
    char dir_name[128];
    DIR *dirp;
    struct dirent *dp;
    struct stat dir_stat;

    // 参数传递进来的目录不存在，直接返回
    if ( 0 != access(dir, F_OK) ) {
        return 0;
    }

    // 获取目录属性失败，返回错误
    if ( 0 > stat(dir, &dir_stat) ) {
        perror("get directory stat error");
        return -1;
    }

    if ( S_ISREG(dir_stat.st_mode) ) {  // 普通文件直接删除
        remove(dir);
    } else if ( S_ISDIR(dir_stat.st_mode) ) {   // 目录文件，递归删除目录中内容
        dirp = opendir(dir);
        while ( (dp=readdir(dirp)) != NULL ) {
            // 忽略 . 和 ..
            if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) ) {
                continue;
            }
            
            sprintf(dir_name, "%s/%s", dir, dp->d_name);
            char_list[1] = dir_name;
            fun_remove_dir(char_list);   // 递归调用
        }
        closedir(dirp);

        rmdir(dir);     // 删除空目录
    } else {
        perror("unknow file type!");    
    }

    }
    return 1;   
}

