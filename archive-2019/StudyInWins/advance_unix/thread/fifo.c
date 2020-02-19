#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

void * readfifo(void *arg)
{
    int fd = *((int *)arg);
    int rt;
    char buf[1024];
    
    while(1)
    {
        rt = read(fd,buf,1024);
        if(0 == rt)
        {
            break;
        }
        write(STDOUT_FILENO,buf,rt);
    }

    return NULL;
}

int main(int argc,char **argv)
{
    int a2b;
    int b2a;

    int i,n,rt;
    char buf[1024];
    
    struct pollfd trans[2];
    int pollid;
    int quit = 0;

    pthread_t tipid;

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
        
        pthread_create(&tipid,NULL,readfifo,(void *)&b2a);

        while(1)
        {
            rt = read(STDIN_FILENO,buf,1024);
            if(0 == rt)
            {
                break;
            }
            write(a2b,buf,rt);
        }

        pthread_join(tipid,NULL);
        close(a2b);
        close(b2a);
    }

    else if(0 == strcmp(argv[1],"b"))
    {
        printf("Mode b print to a:\n");
        
        a2b = open("a2b",O_RDONLY);
        b2a = open("b2a",O_WRONLY);
        
        pthread_create(&tipid,NULL,readfifo,(void *)&a2b);

        while(1)
        {
            rt = read(STDIN_FILENO,buf,1024);
            if(0 == rt)
            {
                break;
            }
            write(b2a,buf,rt);
        }
        
        pthread_join(tipid,NULL);
        close(a2b);
        close(b2a);
    }

    else
    {
        printf("please input a or b!\n");
        return 0;
    }

}
