#include "ls.h"
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
char* get_mode(mode_t m,char* str)//显示文件读写权限函数
{
   if(S_ISREG(m))
   	strcpy(str,"-");
   else if(S_ISDIR(m))
   	strcpy(str,"d");
   else if(S_ISCHR(m))
   	strcpy(str,"c");
   else if(S_ISBLK(m))
   	strcpy(str,"b");
   else if(S_ISFIFO(m))
   	strcpy(str,"f");
   else if(S_ISLNK(m))
   	strcpy(str,"l");
   else if(S_ISSOCK(m))
   	strcpy(str,"n");

   // 属主权限
   strcat(str,m&S_IRUSR?"r":"-");
   strcat(str,m&S_IWUSR?"w":"-");
   strcat(str,m&S_IXUSR?"x":"-");

   // 同组权限
   strcat(str,m&S_IRGRP?"r":"-");
   strcat(str,m&S_IWGRP?"w":"-");
   strcat(str,m&S_IXGRP?"x":"-");

   // 其它权限
   strcat(str,m&S_IROTH?"r":"-");
   strcat(str,m&S_IWOTH?"w":"-");
   strcat(str,m&S_IXOTH?"x":"-");

   return str;
}
int _time(int year)//计算是否是闰年函数
{
   if(year%4==0 && year%100 !=0 || year%400 == 0)
   	return 29;
   return 28;
}
void time_ch(time_t num)//通过秒数来计算日期
{
   int year=1970;
   int month =1;
   int day =1;
   num = num + 8*3600;
   while(num >= 86400)
{
   	num-=86400;
   	day++;
   	if(month==1 && day == 32)
   	{
   		month++; 
   		day =1;
   	}
   	else if(month == 2 && day ==_time(year)+1)
   	{
   		month++;
   		day =1;
   	}
   	else if(month == 3 && day == 32)
   	{
   		month++;
   		day =1;
   	}
   	else if(month == 4 && day == 31)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 5 && day == 32)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 6 && day == 31)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 7 && day == 32)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 8 && day == 32)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 9 && day == 31)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 10 && day == 32)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 11 && day == 31)
   	{
   		month++;
   		day=1;
   	}
   	else if(month == 12 && day == 32)
   	{
   		month=1;
   		day=1;
   		year++;
   	}
   	
   }
   int hour = num/3600;
   int minute =num/60 -hour*60;
   printf("%2d月 %2d %2d:%2d ",month,day,hour,minute);
}



int fun_ls(char** char_list)//主函数
{
   char* dir_name=".";
   if(char_list[1]!=NULL)
   {
   	dir_name = char_list[1];
   }
   DIR* dp=opendir(dir_name);
   if(NULL == dp)
   {
   	perror("opendir");
   	return -1;
   }
   struct dirent* de=readdir(dp);
   for(;de;de=readdir(dp))
   {
   	if('.'==de->d_name[0]) continue;
   	//通过文件名获得文件信息
   	struct stat s;
   	int ret = lstat(de->d_name,&s);
   	if(0 > ret)
   	{
   		perror("stat");
   		return -1;
   	}
   	char str[11] = {};
   	printf("%s ",get_mode(s.st_mode,str));//类型
   	struct passwd *passwd;
   	passwd = getpwuid(s.st_uid);
   	printf ("%s ", passwd->pw_name);//主名
   	struct group *group;
   	group = getgrgid(passwd->pw_gid);
   	printf ("%s ", group->gr_name); //组名
   	printf("%5lu ",s.st_size);//大小
   	time_ch(s.st_mtime);//时间
   	printf("%s\t",de->d_name);//文件名
   	printf("\n");
   }
   closedir(dp);
   return 1;
}
