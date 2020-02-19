#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc,char **argv)
{
    int rt;
    int i = 0;
    int fd1;

    pid_t pid;
    pid_t ppid;

    int p2c[2];
    int c2p[2];

    char *arg[1024];
    char filename[1024];
    char buf[1024] = {0};

    rt = pipe(p2c);
    if(-1 == rt)
    {
        printf("p2c pipe init failed!\n");
        return -1;
    }

    rt = pipe(c2p);
    if(-1 == rt)
    {
        printf("c2p pipe init failed!\n");
        return -1;
    }

    pid = fork();

    if(0 == pid)
    {
        close(p2c[1]);
        close(c2p[0]);
        
        dup2(p2c[0],STDIN_FILENO);
        close(p2c[0]);

        dup2(c2p[1],STDOUT_FILENO);
        close(c2p[1]);

        arg[0] = "./a2A";
        arg[1] = NULL;
        rt = execv("./a2A",arg);
        if(-1 == rt)
        {
            printf("the child execut failed!\n");
        }
    }
    else
    {
        close(p2c[0]);
        close(c2p[1]);
        while(1)
        {
            rt = read(STDIN_FILENO,buf,1024);
            if(0 == rt)
            {
                break;
            }
            write(p2c[1],buf,rt);
            buf[0] = 0;
            
            rt = read(c2p[0],buf,1024);
            if(0 == rt)
            {
                break;
            }
            write(STDOUT_FILENO,buf,rt);
            buf[0] = 0;
        }
        close(p2c[1]);
        close(c2p[0]);
        wait(&rt);
        if(WIFEXITED(rt))
        {
            printf("child exit normal!\n");
            printf("exit:%d\n",rt);
        }
    }
    return 0;
}
