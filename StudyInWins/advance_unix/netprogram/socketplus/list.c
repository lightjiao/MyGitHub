#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


static struct netsocket* newnetsocket(int acceptsocket)
{
    struct netsocket *newsocket;
    newsocket = malloc(sizeof(struct netsocket));
    if(NULL == newsocket)
    {
        printf("cannot malloc new acceptsocket!\n");
        return NULL;
    }

    newsocket->socketfd = acceptsocket;
    strcpy(newsocket->myname,"");
    newsocket->pre = NULL;
    newsocket->next = NULL;
    
    return newsocket;
}


struct netsocket* addnetsocket(struct netsocket *phead,int acceptsocket)
{
    struct netsocket *tmpsocket;
    
    tmpsocket = newnetsocket(acceptsocket);
    
    if(NULL == phead)
    {
        phead = tmpsocket;
        return phead;
    }

    phead->pre = tmpsocket;
    tmpsocket->next = phead;
    tmpsocket->pre = NULL;

    phead = tmpsocket;

    return phead;
}

struct netsocket* delnetsocket(struct netsocket *phead,int acceptsocket)
{
    struct netsocket *tmpsocket = phead;

    while(NULL != tmpsocket)
    {
        if(acceptsocket == tmpsocket->socketfd)
        {
            if(NULL == tmpsocket->pre)
            {
                phead = tmpsocket->next;
                if(NULL != phead)
                {
                    phead->pre = NULL;
                }
            }
            else if(NULL == tmpsocket->next)
            {
                tmpsocket->pre->next = NULL;
            }
            else
            {
                tmpsocket->next->pre = tmpsocket->pre;
                tmpsocket->pre->next = tmpsocket->next;
            }
            free(tmpsocket);
            break;
        }
        tmpsocket = tmpsocket->next;
    }
    return phead;
}






















