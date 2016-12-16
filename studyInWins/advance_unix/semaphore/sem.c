#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#define SHM_KEY 0X6000
#define SEM_KEY 0x7000


union semun
{
    int val;                        // for SETVAL
    struct semid_ds *buf;           // for IPC_STAT and IPC_SET
    unsigned short *array;          // for GETALL and SETALL
};

int main(int argc,char **argv)
{
    int rt;
    int sourcefile;
    int destfile;
    
    int shmid;
    char *pshm;

    int semid;
    union semun s2d;
    union semun d2s;
    struct sembuf semoparray[2];

    char sourcefilename[1024];
    char destfilename[1024];
    char buf[4096];
    
    //////////////////////////////////////////////////////////////// send process
    
    if(0 == strcmp(argv[1],"send"))
    {
        //////////////////////////////////////////////////////////// creat shm 
        
        shmid = shmget(SHM_KEY,4096,IPC_CREAT|0666);
        if(-1 == shmid)
        {
            printf("cannot get shm\n");
            return -1;
        }
        
        pshm = shmat(shmid,NULL,0);
        if(-1 == (int)pshm)
        {
            printf("cannot attach shm\n");
            shmctl(shmid,IPC_RMID,NULL);
            return -1;
        }


        /////////////////////////////////////////////////////////// creat sem and init
        
        semid = semget(SEM_KEY,2,IPC_CREAT|0666);
        if(-1 == semid)
        {
            printf("cannot get sem");
            shmdt(pshm);
            shmctl(shmid,IPC_RMID,NULL);
            return -1;
        }
        
        s2d.val = 1;
        d2s.val = 0;

        semctl(semid,0,SETVAL,s2d);
        semctl(semid,1,SETVAL,d2s);
        

        /////////////////////////////////////////////////////////  open source file
        
        printf("please input the file you want sent:");
        scanf("%s",&sourcefilename);
     
        sourcefile = open(sourcefilename,O_RDONLY);
        if(-1 == sourcefile)
        {
            printf("sourcefile %s is not exist!\n",sourcefilename);
            return -1;
        }

        
        //////////////////////////////////////////////////////// trans 

        while(1)
        {
            semoparray[0].sem_num = 0;
            semoparray[0].sem_op = -1;
            semoparray[0].sem_flg = 0;
            semop(semid,semoparray,1);

            rt = read(sourcefile,pshm+sizeof(int),4096 - sizeof(int));
            *((int *)pshm) = rt;
            
            semoparray[0].sem_num = 1;
            semoparray[0].sem_op = 1;
            semoparray[0].sem_flg = 0;
            semop(semid,semoparray,1);
            
            if(0 == rt)
            {
                semoparray[0].sem_num = 0;
                semoparray[0].sem_op = -1;
                semoparray[0].sem_flg = 0;
                semop(semid,semoparray,1);
                break;
            }
        }

        
        ///////////////////////////////////////////////////// clse all

        close(sourcefile);
        shmdt(pshm);
        shmctl(shmid,IPC_RMID,NULL);
        semctl(semid,2,IPC_RMID);
        return 0;
    }
    
    
    ///////////////////////////////////////////////////////////////// recieve process

    else if(0 == strcmp(argv[1],"recieve"))
    {
        /////////////////////////////////////////////////// get shm

        shmid = shmget(SHM_KEY,4096,0);
        if(-1 == shmid)
        {
            printf("cannot get shm \n");
            return -1;
        }
        pshm = shmat(shmid,NULL,SHM_RDONLY);
        if(-1 == (int)pshm)
        {
            printf("cannot attench shm");
            shmctl(shmid,IPC_RMID,NULL);
            return -1;
        }
        
       
        ////////////////////////////////////////////////// get sem

        semid = semget(SEM_KEY,2,0);
        if(-1 == semid)
        {
            printf("cannot get sem");
            return -1;
        }
      

        //////////////////////////////////////////////// open dest file

        printf("please input the file you want save:");
        scanf("%s",&destfilename);
     
        destfile = open(destfilename,O_WRONLY|O_CREAT|O_EXCL,0666);
        if(-1 == destfile)
        {
            printf("destfile %s cannot open or it's already exist!\n",destfilename);
            return -1;
        }


        ////////////////////////////////////////////////// recieve

        while(1)
        {
            semoparray[0].sem_num = 1;
            semoparray[0].sem_op = -1;
            semoparray[0].sem_flg = 0;
            semop(semid,semoparray,1);
            
            rt = *((int *)pshm);

            if(0 == rt)
            {
                semoparray[0].sem_num = 0;
                semoparray[0].sem_op = 1;
                semoparray[0].sem_flg = 0;
                semop(semid,semoparray,1);
                break;
            }
            
            write(destfile,pshm+sizeof(int),rt);
            
            semoparray[0].sem_num = 0;
            semoparray[0].sem_op = 1;
            semoparray[0].sem_flg = 0;
            semop(semid,semoparray,1);

        }
  

        /////////////////////////////////// clse all

        close(destfile);
        shmdt(pshm);
        shmctl(shmid,IPC_RMID,NULL);
    }
    
    
    ///////////////////////////////////////////////////////////////// tips for input argv
    
    else
    {
        printf("printf please argv send or recieve!\n");
        return -1;
    }
}
