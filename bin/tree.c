#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "tree.h"

char *father_vline = "│   ";
char *block="    ";  //边界空格
char *child_level="├── ";  //中间文件c
char *last_file="└── ";  //最后一个文件
char *level_sum;

/*
4->目录
8->文件
10->符号链接
*/

void tree_dirs(){
    int total_num = 0;
    int cur_num = 0;
    DIR *cur_dir;
    struct dirent *cur_dirent;
    cur_dir = opendir("./");  //打开当前目录

    while ((cur_dirent = readdir(cur_dir)) != NULL)   //计数
    {
        if ((strcmp(cur_dirent->d_name, ".")==0) || (strcmp(cur_dirent->d_name, "..")==0))  //不考虑 . 和 ..
        {
            continue;
        }
        if (cur_dirent->d_type == 4)
        {
            total_num++;
        }else if (cur_dirent->d_type == 10)
        {
            total_num++;
        }
    }
    closedir(cur_dir);

    cur_dir = opendir("./");  //再次打开当前目录
    while ((cur_dirent = readdir(cur_dir)) != NULL) 
    {
        if ((strcmp(cur_dirent->d_name, ".")==0) || (strcmp(cur_dirent->d_name, "..")==0))  //不考虑 . 和 ..
        {
            continue;
        }
        if (cur_dirent->d_type == 4)      //文件夹处理
        {
            cur_num++;
            if (cur_num == total_num)
            {   
                printf("%s%s\033[46;30m%s\033[0m\n", level_sum, last_file, cur_dirent->d_name);
                int len1 = strlen(level_sum);
                int len2 = strlen(block);

                strcat(level_sum, block);  //字符串拼接

                chdir(cur_dirent->d_name);  //cd name
                tree_dirs(cur_dirent->d_name);

                //删除block
                int i = len1;
                for (; i < len1+len2; i++)
                {
                    level_sum[i] = 0;
                }
                level_sum[i] = '\0';

                chdir("../");  // cd ../

            }else  //不是最后一项
            {
                printf("%s%s\033[46;30m%s\033[0m\n", level_sum, child_level, cur_dirent->d_name);
                int len1 = strlen(level_sum);
                int len2 = strlen(father_vline);

                strcat(level_sum, father_vline);
                chdir(cur_dirent->d_name);   // cd name
                tree_dirs(cur_dirent->d_name); 
                int i = len1;
                for (; i < len1+len2; i++)
                {
                    level_sum[i] = 0;
                }
                level_sum[i] = '\0';

                chdir("../");    //cd ../
            }   
              
        }else if (cur_dirent->d_type == 10)   //符号链接处理
        {
            cur_num++;
            if (cur_num == total_num)
            {
                char* buf = (char*)malloc(1024);
                readlink(cur_dirent->d_name,buf,1023);

                struct stat s_buf;
                stat(buf, &s_buf);
                if (S_ISDIR(s_buf.st_mode))
                {
                    printf("%s%s\033[34m%s\033[0m -> \033[46;30m%s\033[0m\n",level_sum, last_file, cur_dirent->d_name, buf);
                    free(buf);
                    int len1 = strlen(level_sum);
                    int len2 = strlen(block);
                    strcat(level_sum, block);

                    chdir(cur_dirent->d_name);

                    tree_dirs(cur_dirent->d_name); 
                    int i = len1;
                    for (; i < len1+len2; i++)
                    {
                        level_sum[i] = 0;
                    }
                    level_sum[i] = '\0';

                    chdir("../");
                }

            }else
            {
                char* buf = (char*)malloc(1024);
                readlink(cur_dirent->d_name,buf,1023);
                struct stat s_buf;
                stat(buf, &s_buf);

                if (S_ISDIR(s_buf.st_mode))
                {                 
                    printf("%s%s\033[34m%s\033[0m -> \033[46;30m%s\033[0m\n", level_sum, child_level, cur_dirent->d_name, buf);
                    free(buf);
                    int len1 = strlen(level_sum);
                    int len2 = strlen(father_vline);

                    strcat(level_sum, father_vline);

                    chdir(cur_dirent->d_name);
                    tree_dirs(cur_dirent->d_name); 
                    int i = len1;
                    for (; i < len1+len2; i++)
                    {
                        level_sum[i] = 0;
                    }
                    level_sum[i] = '\0';  
                    chdir("../");
                }
            }     
        }
    }
    closedir(cur_dir);
}


void tree_normal(){
    int total_num = 0;
    int cur_num = 0;
    DIR *cur_dir;
    struct dirent *cur_dirent;
    cur_dir = opendir("./");  //打开当前目录

    while ((cur_dirent = readdir(cur_dir)) != NULL)   //计数
    {
        if ((cur_dirent->d_name)[0] == '.')  //不考虑 . 和 .. 和隐藏文件
        {
            continue;
        }
        if ((cur_dirent->d_type == 4) || (cur_dirent->d_type == 10) || (cur_dirent->d_type == 8))
        {
            total_num++;
        }
    }
    closedir(cur_dir);
    
    cur_dir = opendir("./");  //再次打开当前目录
    while ((cur_dirent = readdir(cur_dir)) != NULL) 
    {
        if ((cur_dirent->d_name)[0] == '.')  //不考虑 . 和 .. 和隐藏文件
        {
            continue;
        }
        if (cur_dirent->d_type == 4)      //文件夹处理
        {
            cur_num++;
            if (cur_num == total_num)
            {   
                printf("%s%s\033[46;30m%s\033[0m\n", level_sum, last_file, cur_dirent->d_name);
                int len1 = strlen(level_sum);
                int len2 = strlen(block);

                strcat(level_sum, block);  //字符串拼接

                chdir(cur_dirent->d_name);  //cd name
                tree_normal();

                //删除block
                int i = len1;
                for (; i < len1+len2; i++)
                {
                    level_sum[i] = 0;
                }
                level_sum[i] = '\0';

                chdir("../");  // cd ../

            }else  //不是最后一项
            {
                printf("%s%s\033[46;30m%s\033[0m\n", level_sum, child_level, cur_dirent->d_name);
                int len1 = strlen(level_sum);
                int len2 = strlen(father_vline);

                strcat(level_sum, father_vline);
                chdir(cur_dirent->d_name);   // cd name
                tree_normal();
                int i = len1;
                for (; i < len1+len2; i++)
                {
                    level_sum[i] = 0;
                }
                level_sum[i] = '\0';

                chdir("../");    //cd ../
            }   
              
        }else if (cur_dirent->d_type == 10)   //符号链接处理
        {
            cur_num++;
            if (cur_num == total_num)
            {
                char* buf = (char*)malloc(1024);
                readlink(cur_dirent->d_name,buf,1023);

                struct stat s_buf;
                stat(buf, &s_buf);
                if (S_ISDIR(s_buf.st_mode))
                {
                    printf("%s%s\033[34m%s\033[0m -> \033[46;30m%s\033[0m\n",level_sum, last_file, cur_dirent->d_name, buf);
                    free(buf);
                    int len1 = strlen(level_sum);
                    int len2 = strlen(block);
                    strcat(level_sum, block);

                    chdir(cur_dirent->d_name);

                    tree_normal(); 
                    int i = len1;
                    for (; i < len1+len2; i++)
                    {
                        level_sum[i] = 0;
                    }
                    level_sum[i] = '\0';

                    chdir("../");
                }else
                {
                    printf("%s%s\033[34m%s\033[0m -> %s\n",level_sum, last_file, cur_dirent->d_name, buf);
                    free(buf);
                }
            }else
            {
                char* buf = (char*)malloc(1024);
                readlink(cur_dirent->d_name,buf,1023);
                struct stat s_buf;
                stat(buf, &s_buf);

                if (S_ISDIR(s_buf.st_mode))
                {                 
                    printf("%s%s\033[34m%s\033[0m -> \033[46;30m%s\033[0m\n", level_sum, child_level, cur_dirent->d_name, buf);
                    free(buf);
                    int len1 = strlen(level_sum);
                    int len2 = strlen(father_vline);

                    strcat(level_sum, father_vline);

                    chdir(cur_dirent->d_name);
                    tree_normal(); 
                    int i = len1;
                    for (; i < len1+len2; i++)
                    {
                        level_sum[i] = 0;
                    }
                    level_sum[i] = '\0';  
                    chdir("../");
                }else
                {
                    printf("%s%s\033[34m%s\033[0m -> %s\n",level_sum, child_level, cur_dirent->d_name, buf);
                    free(buf);
                }
            }     
        }else if (cur_dirent->d_type == 8)
        {
            cur_num++;
            if (cur_num == total_num)
            {
                printf("%s%s%s\n", level_sum, last_file, cur_dirent->d_name);
            }else
            {
                printf("%s%s%s\n", level_sum, child_level, cur_dirent->d_name);
            }
            
        }
        
    }
    closedir(cur_dir);
}

void tree_all(){
    int total_num = 0;
    int cur_num = 0;
    DIR *cur_dir;
    struct dirent *cur_dirent;
    cur_dir = opendir("./");  //打开当前目录

    while ((cur_dirent = readdir(cur_dir)) != NULL)   //计数
    {
        if ((strcmp(cur_dirent->d_name, ".")==0) || (strcmp(cur_dirent->d_name, "..")==0))  //不考虑 . 和 ..
        {
            continue;
        }
        if ((cur_dirent->d_type == 4) || (cur_dirent->d_type == 10) || (cur_dirent->d_type == 8))
        {
            total_num++;
        }
    }
    closedir(cur_dir);
    
    cur_dir = opendir("./");  //再次打开当前目录
    while ((cur_dirent = readdir(cur_dir)) != NULL) 
    {
        if ((strcmp(cur_dirent->d_name, ".")==0) || (strcmp(cur_dirent->d_name, "..")==0))  //不考虑 . 和 ..
        {
            continue;
        }
        if (cur_dirent->d_type == 4)      //文件夹处理
        {
            cur_num++;
            if (cur_num == total_num)
            {   
                printf("%s%s\033[46;30m%s\033[0m\n", level_sum, last_file, cur_dirent->d_name);
                int len1 = strlen(level_sum);
                int len2 = strlen(block);

                strcat(level_sum, block);  //字符串拼接

                chdir(cur_dirent->d_name);  //cd name
                tree_all();

                //删除block
                int i = len1;
                for (; i < len1+len2; i++)
                {
                    level_sum[i] = 0;
                }
                level_sum[i] = '\0';

                chdir("../");  // cd ../

            }else  //不是最后一项
            {
                printf("%s%s\033[46;30m%s\033[0m\n", level_sum, child_level, cur_dirent->d_name);
                int len1 = strlen(level_sum);
                int len2 = strlen(father_vline);

                strcat(level_sum, father_vline);
                chdir(cur_dirent->d_name);   // cd name
                tree_all();
                int i = len1;
                for (; i < len1+len2; i++)
                {
                    level_sum[i] = 0;
                }
                level_sum[i] = '\0';

                chdir("../");    //cd ../
            }   
              
        }else if (cur_dirent->d_type == 10)   //符号链接处理
        {
            cur_num++;
            if (cur_num == total_num)
            {
                char* buf = (char*)malloc(1024);
                readlink(cur_dirent->d_name,buf,1023);

                struct stat s_buf;
                stat(buf, &s_buf);
                if (S_ISDIR(s_buf.st_mode))
                {
                    printf("%s%s\033[34m%s\033[0m -> \033[46;30m%s\033[0m\n",level_sum, last_file, cur_dirent->d_name, buf);
                    free(buf);
                    int len1 = strlen(level_sum);
                    int len2 = strlen(block);
                    strcat(level_sum, block);

                    chdir(cur_dirent->d_name);

                    tree_all(); 
                    int i = len1;
                    for (; i < len1+len2; i++)
                    {
                        level_sum[i] = 0;
                    }
                    level_sum[i] = '\0';

                    chdir("../");
                }else
                {
                    printf("%s%s\033[34m%s\033[0m -> %s\n",level_sum, last_file, cur_dirent->d_name, buf);
                    free(buf);
                }
            }else
            {
                char* buf = (char*)malloc(1024);
                readlink(cur_dirent->d_name,buf,1023);
                struct stat s_buf;
                stat(buf, &s_buf);

                if (S_ISDIR(s_buf.st_mode))
                {                 
                    printf("%s%s\033[34m%s\033[0m -> \033[46;30m%s\033[0m\n", level_sum, child_level, cur_dirent->d_name, buf);
                    free(buf);
                    int len1 = strlen(level_sum);
                    int len2 = strlen(father_vline);

                    strcat(level_sum, father_vline);

                    chdir(cur_dirent->d_name);
                    tree_all(); 
                    int i = len1;
                    for (; i < len1+len2; i++)
                    {
                        level_sum[i] = 0;
                    }
                    level_sum[i] = '\0';  
                    chdir("../");
                }else
                {
                    printf("%s%s\033[34m%s\033[0m -> %s\n",level_sum, child_level, cur_dirent->d_name, buf);
                    free(buf);
                }
            }     
        }else if (cur_dirent->d_type == 8)
        {
            cur_num++;
            if (cur_num == total_num)
            {
                printf("%s%s%s\n", level_sum, last_file, cur_dirent->d_name);
            }else
            {
                printf("%s%s%s\n", level_sum, child_level, cur_dirent->d_name);
            }
            
        }
        
    }
    closedir(cur_dir);
}

void tip(){
    printf("    默认遍历展示所有非隐藏文件\n");
    printf("    可选项 -[option]:\n");
    printf("    -a -----------> 展示所有文件\n");
    printf("    -d -----------> 只展示文件夹\n");
}

int fun_tree(char** argv)
{
    level_sum = (char*)malloc(4096);   //linux路径的最大长度
    char dirName[255];  //linux文件名的最大长度
    if (argv[1] == NULL)  //不带参，当前目录
    {
        strcpy(dirName, ".");
        DIR *cur_dir;
        cur_dir = opendir(dirName);
        if (cur_dir != NULL)
        {
            printf("\033[46;30m%s\033[0m\n", dirName);
        }else
        {
            printf("\033[31mopen dir error! \033[0m\n");
            exit(1);
        }
        closedir(cur_dir);
        chdir(dirName);  //切换到目标目录
        tree_normal();
        
    }else if (argv[2]==NULL) //一个参数
    {
        strcpy(dirName, argv[1]);
        DIR *cur_dir;
        cur_dir = opendir(dirName);
        if (cur_dir != NULL)
        {
            printf("\033[46;30m%s\033[0m\n", dirName);
        }else
        {
            printf("\033[31mopen dir error! \033[0m\n");
            exit(1);

        }
        
        closedir(cur_dir);
        chdir(dirName);  //切换到目标目录
        tree_normal();
        
    }else if (argv[3]==NULL) //两个参数
    {
        if (strcmp(argv[1], "-a")==0)
        {
            strcpy(dirName, argv[2]);
            DIR *cur_dir;
            cur_dir = opendir(dirName);
            if (cur_dir != NULL)
            {
                printf("\033[46;30m%s\033[0m\n", dirName);
            }else
            {
                printf("\033[31mopen dir error! \033[0m\n");
                exit(1);
                
            }
            
            closedir(cur_dir);
            chdir(dirName);  //切换到目标目录
            tree_all();
            
        }else if (strcmp(argv[1], "-d")==0) 
        {
            strcpy(dirName, argv[2]);
            DIR *cur_dir;
            cur_dir = opendir(dirName);
            if (cur_dir != NULL)
            {
                printf("\033[46;30m%s\033[0m\n", dirName);
            }else
            {
                printf("\033[31mopen dir error! \033[0m\n");
                exit(1);

            }
            closedir(cur_dir);
            chdir(dirName);  //切换到目标目录
            tree_dirs();
        }else
        {
            tip();
        }
    }else //3个以上参数
    {
        printf("\033[31mtoo many arguments!\033[0m\n");
    }

    return 1;
}