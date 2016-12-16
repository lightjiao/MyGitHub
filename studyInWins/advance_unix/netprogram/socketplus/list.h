

#ifndef __LIST_H__
#define __LIST_H__

struct netsocket
{
    int socketfd;
    char myname[20];
    struct netsocket *pre;
    struct netsocket *next;
};


extern struct netsocket* addnetsocket(struct netsocket *phead,int acceptsocket);
extern struct netsocket* delnetsocket(struct netsocket *phead,int acceptsocket);


#endif
