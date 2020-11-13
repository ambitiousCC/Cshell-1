#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <libgen.h>
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

int fun_rm(char** argv)
{
    if(argv[3]==NULL)
    {
        printf("Usage:%s filename\n",basename(argv[0]));
        exit(0);
    }

    if(unlink(argv[1])!=0)
    {
        perror("ulink");
        exit(-1);
    }

    printf("remove %s success!\n",basename(argv[1]));
    return 1;
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
    char dir_name[1024];
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

int fun_mv(char** argv)
{
    FILE * source = fopen(argv[1],"r");
    if(source==NULL)
    {
        perror ("file no exsit!\n");
        exit(0);
    }
    else
    {
        struct stat * statbuf=(struct stat *)malloc(sizeof(statbuf));
        stat(argv[2], statbuf); //判断目标路径是一个普通文件还是一个目录
        if(S_ISDIR (statbuf->st_mode)) //目标是个目录
        {
                int i,j,k=0;
                //因为目标路径是一个目录，所以默认拷贝一个和源文件名字一样的名字
                //要找到源文件的名字，就要找源路径最后一个'/'后面的字符串就是源文件名！！
                for(i=strlen(argv[1])-1;i>=0;i--)
                {
                    if(argv[1][i]=='/') //找到了最后一个'/'的下标
                    {
                        break; //找到就退出 ，保留'/'下标为i
                    }
                }
                char source_file_name[1024]={};//用来存储源文件的名字
                for(j=i+1;j<strlen(argv[1]);j++)
                {   //把源路径最后一个'/'后面的字符串给source_file_name,它就是源文件名字
                    source_file_name[k++]=argv[1][j];
                }
                //如果目标路径最后面没有‘/’，则需要加一个'/'
                if(argv[2][strlen(argv[2])-1]!='/') 
                {
                    strcat (argv[2],"/");
                }
                //把目标路径和源文件名拼接起来，成为一个目标文件名，并创建打开它
                FILE * target = fopen(strcat (argv[2],source_file_name),"w+");
                while(!feof(source))
                {   //把源文件内容全部传给目标文件
                    char  buf[10]={};
                    fread (buf,1,10,source); 
                    fwrite (buf,1,10, target);
                }   
                    fclose(target);
        }
        else//目标路径是个文件
        {
            FILE * target = fopen(argv[2],"w+");
            while(!feof(source))
            {//把源文件内容全部传给目标文件
                char  buf[10]={};
                fread (buf,1,10,source);
                fwrite (buf,1,10, target);
            }   
                fclose(target);
        }
        
    }
    remove(argv[1]);  //删除源文件
    fclose(source);
    printf("mv %s success!\n",basename(argv[1]));
    return 1;
}
