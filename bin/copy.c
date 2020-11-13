#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "copy.h"

#define BUFFER_SIZE 1024

int fun_copy(char **argv) 
{
	int from_fd,to_fd;
	int bytes_read,bytes_write;

	char buffer[BUFFER_SIZE];
	char*ptr;

	if(argv[2]==NULL)//如果不够2个参数
	{
		fprintf(stderr,"Usage:%s fromfile tofile \n\a",argv[0]);
		exit(1);
	}

	//open original file
	if((from_fd=open(argv[1],O_RDONLY))==-1)
	{
		fprintf(stderr,"Open %sError: %s\n",argv[1],strerror(errno));
		exit(1);
	}

	printf("openning %s...\n",argv[1]);

	//create target file
	if((to_fd=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1)
	{
		fprintf(stderr,"Open %sError: %s\n",argv[2],strerror(errno));
		exit(1);
	}

	printf("creating %s...\n",argv[2]);
	
	//classical codes of copy file
	while(bytes_read=read(from_fd,buffer,BUFFER_SIZE))
	{
		//error
		if((bytes_read==-1)&&(errno!=EINTR)) break;
		else if(bytes_read>0)
		{
			ptr=buffer;
			while(bytes_write=write(to_fd,ptr,bytes_read))
			{
				//error
				if((bytes_write==-1)&&(errno!=EINTR)) break;
				//all read btyes
				else if(bytes_write==bytes_read) break;
				//continue writing
				else if(bytes_write>0)
				{
					ptr+=bytes_write;
					bytes_read-=bytes_write;
				}
			}
			//erro when write
			if(bytes_write==-1) break;
		}
	}
	close(from_fd);
	close(to_fd);

	printf("%s\n","finished");

	return 1;
}
