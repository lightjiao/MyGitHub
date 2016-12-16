#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    int a2b;
    int b2a;

    int i,n,rt;
    char buf[1024];
    
    struct pollfd trans[2];
    int pollid;
    int quit = 0;

    if(argc < 2)
    {
        printf("too little argc!\n");
        return -1;
    }

    if(0 == strcmp(argv[1],"a"))
    {
        printf("Mode a print to b:\n");
       
        a2b = open("a2b",O_WRONLY);
        b2a = open("b2a",O_RDONLY);
        
        trans[0].fd = STDIN_FILENO;
        trans[0].events = POLLIN;
        trans[0].revents = 0;
        
        trans[1].fd = b2a;
        trans[1].events = POLLIN;
        trans[1].revents = 0;

        while(0 == quit)
        {
            pollid = poll(trans,2,-1);
            if(pollid <= 0)
            {
                printf("poll failed!\n");
                continue;
            }
            for(i=0;i<2;i++)
            {
                if(0 != trans[i].revents)
                {
                    rt = read(trans[i].fd,buf,1024);
                    if(0 == rt)
                    {
                        quit = 1;
                        break;
                    }
                    if(0 == i)
                    {
                        write(a2b,buf,rt);
                    }
                    else
                    {
                        write(STDOUT_FILENO,buf,rt);
                    }
                }
            }
        }
    }

    else if(0 == strcmp(argv[1],"b"))
    {
        printf("Mode b print to a:\n");
        
        a2b = open("a2b",O_RDONLY);
        b2a = open("b2a",O_WRONLY);
        
        trans[0].fd = STDIN_FILENO;
        trans[0].events = POLLIN;
        trans[0].revents = 0;
        
        trans[1].fd = a2b;
        trans[1].events = POLLIN;
        trans[1].revents = 0;

        while(0 == quit)
        {
            pollid = poll(trans,2,-1);
            if(pollid <= 0)
            {
                printf("poll failed!\n");
                continue;
            }
            for(i=0;i<2;i++)
            {
                if(0 != trans[i].revents)
                {
                    rt = read(trans[i].fd,buf,1024);
                    if(0 == rt)
                    {
                        quit = 1;
                        break;
                    }
                    if(0 == i)
                    {
                        write(b2a,buf,rt);
                    }
                    else
                    {
                        write(STDOUT_FILENO,buf,rt);
                    }
                }
            }
        }
    }

    else
    {
        printf("please input a or b!\n");
        return 0;
    }

}
