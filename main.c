#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "make_log.h"

int main(int argc,char *argv[])
{
	char		*file_name = NULL;
	
	if(argc < 2)
	{
		printf("usage:./a.out <filename path>\n");
		exit(1);
	}
	
	file_name = argv[1];
	
    pid_t       pid;
    int         fd[2],n;
    char        buf[1024] = {0};
    //memset(buf,0,sizeof(buf));

    int ret =pipe(fd);
    if(ret == -1)
    {
    	//dumpmsg_to_file(module_name, proc_name, __FILE__, __LINE__, __FUNCTION__, ##x)
        LOG("test", "main.c",  __FILE__, __LINE__,__FUNCTION__);
        perror("pipe error");
    }

    
        if((pid = fork()) == -1)
        {
           	LOG("test", "main.c",  __FILE__, __LINE__,__FUNCTION__);
            perror("pipe error");
            exit(1);
        }
        else if(pid == 0)
        {
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execlp("/usr/bin/fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf",file_name,NULL);
        }
        else
        {
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            n = read(fd[0],buf,sizeof(buf));
            LOG("test", "main.c",buf);
            printf("%s hahaha \n",buf);
            wait(NULL);
        }
    

    return 0;
}