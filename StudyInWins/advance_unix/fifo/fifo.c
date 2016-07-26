#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    int a2b;
    int b2a;
    char buf[1024];
    int rt;

    pid_t pid = 0;

    if(argc < 2)
    {
        fprintf(stderr,"too little !\n");
        return -1;
    }
    if(0 == strcmp(argv[1],"a"))
    {
        printf("Mode a print to b:\n");

        pid = fork();

        if(0 == pid)   //////////////////////////////////////////// the child process of a2b
        {
            b2a = open("b2a",O_RDONLY);
            if(-1 == b2a)
            {
                printf("Mode a2b open to read failed!\n");
                return -1;
            }
            while(1)
            {
                rt = read(b2a,buf,1024);
                if(0 == rt)
                {
                    break;
                }
                write(STDOUT_FILENO,buf,rt);
            }
            close(b2a);
        }
        else         /////////////////////////////////////////// the father process of a2b
        {
            a2b = open("a2b",O_WRONLY);
            if(-1 == a2b)
            {
                printf("Mode a2b open to write failed!\n");
                return -1;
            }
            while(1)
            {
                rt = read(STDIN_FILENO,buf,1024);
                if(0 ==rt)
                {
                    break;
                }
                write(a2b,buf,rt);
            }
            close(a2b);
        }
    }
    else if(0 == strcmp(argv[1],"b"))
    {
        printf("Mode b print to a:\n");

        pid = fork();

        if(0 == pid)   //////////////////////////////////////////// the child process of b2a
        {
            a2b = open("a2b",O_RDONLY);
            if(-1 == a2b)
            {
                printf("Mode a2b open to read failed!\n");
                return -1;
            }
            while(1)
            {
                rt = read(a2b,buf,1024);
                if(0 == rt)
                {
                    break;
                }
                write(STDOUT_FILENO,buf,rt);
            }
            close(a2b);
        }
        else         /////////////////////////////////////////// the father process of a2b
        {
            b2a = open("b2a",O_WRONLY);
            if(-1 == b2a)
            {
                printf("Mode a2b open to write failed!\n");
                return -1;
            }
            while(1)
            {
                rt = read(STDIN_FILENO,buf,1024);
                if(0 ==rt)
                {
                    break;
                }
                write(b2a,buf,rt);
            }
        }
    }
    else
    {
        printf("Please input a or b!\n");
    }
    return 0;
}
