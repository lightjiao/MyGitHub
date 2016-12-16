#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"


int a2A(char *buf)
{
    int i;

    for(i=0;0 != buf[i];i++)
    {
        if( (buf[i] <= 'z')&& (buf[i] >= 'a'))
        {
            buf[i] -= 'a'-'A';
            sleep(1);
        }
    }
    return 0;
}

pthread_mutex_t qlock;
pthread_cond_t qcond;

void* startfunc(void *arg)
{
    struct myqueue *que;
    char *buf;

    que = (struct myqueue *)arg;

    while(1)
    {
        pthread_mutex_lock(&qlock);
        while(que->isempty(que))
        {
            pthread_cond_wait(&qcond,&qlock);
        }
        buf = que->get(que);
        pthread_mutex_unlock(&qlock);
        a2A(buf);
        printf("\ntask resault:");
        puts(buf);
        free(buf);
    }
    return NULL;
}

int main()
{
    char buf[1024];
    char *p;
    int rt;

    struct myqueue que;
    
    pthread_t tpid;
    
    initallqueue(&que);
    pthread_mutex_init(&qlock,NULL);
    pthread_cond_init(&qcond,NULL);

    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);
    pthread_create(&tpid,NULL,startfunc,(void *)&que);

    while(1)
    {
        printf("please input task:");
        buf[0] = 0;
        fgets(buf,1024,stdin);
        if(0 == strlen(buf))
        {
            break;
        }
        buf[strlen(buf)-1] = 0;
        if(0 == strlen(buf))
        {
            continue;
        }
        p = malloc(strlen(buf)+1);
        strcpy(p,buf);
        
        printf("task recieve!\n");
        
        pthread_mutex_lock(&qlock);
        rt = que.isempty(&que);
        que.put(&que,p);
        pthread_mutex_unlock(&qlock);
        if(rt)
        {
            pthread_cond_broadcast(&qcond);
        }
    }
}





















