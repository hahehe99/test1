#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "make_log.h"

int main(void)
{
    pid_t       pid;
    int         fd[2],i,n;
    char        buf[1024];

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
        else if(pid > 0)
        {
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execlp("/usr/bin/fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf","a",NULL);
        }
        else
        {
        	sleep(1);
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            n = read(fd[0],buf,sizeof(buf));
            LOG("test", "main.c",buf);
            printf("%s hahaha \n",buf);
        }
    

    return 0;
}