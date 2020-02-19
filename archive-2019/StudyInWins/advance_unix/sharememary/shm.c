#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <fcntl.h>


int main(int argc,char *argv[])
{
    int shmid;
    char *pshm;
    int rt;
    int s2d,sourcefile;
    int d2s,destfile;
    
    char sourcefilename[1024];
    char destfilename[1024];
    char buf[4096];

    if(argc < 2)
    {
        printf("too little argc!\n");
        return -1;
    }

    if(0 == strcmp(argv[1],"w"))
    {
        ///////////////////////////////////////////////////// open source file and pipe
        
        printf("please input the file you want sent:");
        scanf("%s",&sourcefilename);

        sourcefile = open(sourcefilename,O_RDONLY);
        if(-1 == sourcefile)
        {
            printf("file %s is not exist!\n",sourcefilename);
            return -1;
        }

        s2d = open("s2d",O_WRONLY);
        if(-1 == s2d)
        {
            printf("open pipe s2d failed!\n");
            close(sourcefile);
            return -1;
        }

        d2s = open("d2s",O_RDONLY);
        if(-1 == d2s)
        {
            printf("open pipe d2s failed!\n");
            close(s2d);
            close(sourcefile);
            return -1;
        }

        //////////////////////////////////////////////////// creat shm
        
        shmid = shmget(0x6000,4096,IPC_CREAT|0666);
        if(-1 == shmid)
        {
            fprintf(stderr,"cannot get shm!\n");
            return -1;
        }
        pshm = shmat(shmid,NULL,0);
        if(-1 == (int)pshm)
        {
            fprintf(stderr,"cannot attach shmid!\n");
            shmctl(shmid,IPC_RMID,NULL);
            return -1;
        }

        //////////////////////////////////////////////////// trans
        
        while(1)
        {
            rt = read(sourcefile,pshm,4096);
            write(s2d,&rt,sizeof(int));

            if(0 == rt)
            {
                break;
            }

            read(d2s,&rt,sizeof(int));

        }

        /////////////////////////////////////////////////// close all
        
        close(sourcefile);
        close(s2d);
        close(d2s);
        shmdt(pshm);
        shmctl(shmid,IPC_RMID,NULL);

        return 0;
    }
    else
    {
        ////////////////////////////////////////////////// open dest file and pipe

        printf("please input the file you save:");
        scanf("%s",&destfilename);

        destfile = open(destfilename,O_WRONLY|O_CREAT|O_EXCL,0644);
        if(-1 == destfile)
        {
            printf("cannot open dest file or dest file isalready exist!\n");
            return -1;
        }

        s2d = open("s2d",O_RDONLY);
        if(-1 == s2d)
        {
            printf("open pipe s2d failed!\n");
            close(destfile);
            return -1;
        }

        d2s = open("d2s",O_WRONLY);
        if(-1 == d2s)
        {
            printf("open pipe d2s failed!\n");
            close(s2d);
            close(destfile);
            return -1;
        }
        
        /////////////////////////////////////// creat shm

        shmid = shmget(0x6000,4096,0);
        if(-1 == shmid)
        {
            fprintf(stderr,"cannot get shm!\n");
            return -1;
        }
        pshm = shmat(shmid,NULL,0);
        if(-1 == (int)pshm)
        {
            fprintf(stderr,"cannot attach shmid!\n");
            shmctl(shmid,IPC_RMID,NULL);
            return -1;
        }

        //////////////////////////////////////// recieve

        while(1)
        {
            read(s2d,&rt,sizeof(int));
            if(0 == rt)
            {
                break;
            }

            write(destfile,pshm,rt);
            write(d2s,&rt,sizeof(int));

        }

        ///////////////////////////////////////// close all

        close(destfile);
        close(s2d);
        close(d2s);
        shmdt(pshm);
        
        return 0;

    }
}
