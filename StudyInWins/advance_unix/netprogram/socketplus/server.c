#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "msg.h"
#include "list.h"

struct netsocket *netsocketphead = NULL;

pthread_mutex_t netsocketmutex;


///////////////////////////////////////////////////////////////////////////////////////// tell client where server is

void* tellclientby3sec(void *arg)
{
    int rt;
    int val = 1;
    int udpserversocket;
    struct sockaddr_in udpserverin;

    char udpmessage[10];
    struct udpmsghead *udpmsgphead = (struct udpmsghead *)udpmessage;

    udpserversocket = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == udpserversocket)
    {
        printf("udp server cannot socket!\n");
        return ;
    }
    
    udpserverin.sin_family = AF_INET;
    udpserverin.sin_port = htons(UDPPORT);
    udpserverin.sin_addr.s_addr = inet_addr("192.168.1.255");
    memset(udpserverin.sin_zero,0,8);

    rt = setsockopt(udpserversocket,SOL_SOCKET,SO_BROADCAST,&val,sizeof(udpserverin));
    if(-1 == rt)
    {
        printf("cannot setsocketopt!\n");
        return ;
    }

    udpmsgphead->type = htonl(SERVER_BROADCAST_RESPONS);
    udpmsgphead->ip = inet_addr("192.168.1.100");
    udpmsgphead->port = htons(TCPPORT);

    while(1)
    {
        sleep(3);
        rt = sendto(udpserversocket,udpmessage,10,0,(struct sockaddr *)&udpserverin,sizeof(udpserverin));
    }

    return NULL;
}


///////////////////////////////////////////////////////////////////////////////////////// get client message and transmit

void* getmessage(void *arg)
{
    int rt;
    int socketfd;
    int savefile;
    int savefileflag = 0;
    char buf[1024];
    char message[4096];
    int type;
    int msglen;
    char destname[20];
    char *systemname = "system";
    struct netsocket *tmpnetsocket;
    char namelist[4096];

    struct msghead *phead = (struct msghead *)message;

    socketfd = (int)arg;

    while(1)
    {
        recv(socketfd,phead,HEADLEN,MSG_WAITALL);
        type = ntohl(phead->type);
        strcpy(destname,phead->destname);
        msglen = ntohl(phead->msglen);
        
        if(WHO_IS_ONLINE == type)
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////// who is online
        {
            recv(socketfd,message,msglen,MSG_WAITALL);
            
            phead->type = htonl(SINGLE_TALK_MESSAGE);
            strcpy(phead->sourcename,systemname);
            
            pthread_mutex_lock(&netsocketmutex);
            tmpnetsocket = netsocketphead;
            while(NULL != tmpnetsocket)
            {
                if(tmpnetsocket == netsocketphead)
                {
                    strcpy(namelist,tmpnetsocket->myname);
                    strcat(namelist,"   ");
                    rt = 1;
                    continue;
                }
                strcat(namelist,tmpnetsocket->myname);
                rt++;
                if(3 == rt)
                {
                    strcat(namelist,"\n");
                    rt = 0;
                }
                else
                {
                    strcat(namelist,"   ");
                }

                tmpnetsocket = tmpnetsocket->next;
            }
            pthread_mutex_unlock(&netsocketmutex);

            strcpy(message+HEADLEN,namelist);
            write(socketfd,message,HEADLEN+strlen(namelist));
        }

        else if(WHO_AM_I == type) 
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////// who am i
        {
            phead->type = htonl(NAME_SUCCESSFUL);
            
            pthread_mutex_lock(&netsocketmutex);
            tmpnetsocket = netsocketphead;
            while(NULL != tmpnetsocket)
            {
                if(0 == strcmp(tmpnetsocket->myname,phead->sourcename))
                {
                    phead->type = htonl(NAME_REPEAT);
                    break;
                }
                tmpnetsocket = tmpnetsocket->next;
            }
            pthread_mutex_unlock(&netsocketmutex);
            
            write(socketfd,message,HEADLEN);
            
            if(phead->type == ntohl(NAME_SUCCESSFUL))
            {
                tmpnetsocket = netsocketphead;
                while(NULL != tmpnetsocket)
                {
                    if(tmpnetsocket->socketfd == socketfd)
                    {
                        strcpy(tmpnetsocket->myname,phead->sourcename);
                        break;
                    }
                    tmpnetsocket = tmpnetsocket->next;
                }
            }
        }

        else if((TALK_MESSAGE == type)||(START_TRANS_FILE == type)||(TRANS_FILE == type)||(END_TRANS_FILE == type)) 
        /////////////////////////////////////////////////////////////////////////////////////////////////////// send message to everyone and lock
        {
            rt = recv(socketfd,message+HEADLEN,msglen,MSG_WAITALL);
            if((0 == rt)&&(TALK_MESSAGE == type))
            {
                break;
            }

            tmpnetsocket = netsocketphead;
            pthread_mutex_lock(&netsocketmutex);
            while(NULL != tmpnetsocket)
            {
                if(tmpnetsocket->socketfd == socketfd)
                {
                    tmpnetsocket = tmpnetsocket->next;
                    continue;
                }
                write(tmpnetsocket->socketfd,message,rt+HEADLEN);
                tmpnetsocket = tmpnetsocket->next;
            }
            pthread_mutex_unlock(&netsocketmutex);
        }

        else if((SINGLE_TALK_MESSAGE == type)||(SINGLE_START_TRANS_FILE == type)||(SINGLE_TRANS_FILE == type)||(SINGLE_END_TRANS_FILE == type))
        ///////////////////////////////////////////////////////////////////////////////////////////////////// send message to one and lock
        {
            rt = recv(socketfd,message+HEADLEN,msglen,MSG_WAITALL);
            
            pthread_mutex_lock(&netsocketmutex);
            tmpnetsocket = netsocketphead;
            while(NULL != tmpnetsocket)
            {
                if(0 == strcmp(tmpnetsocket->myname,destname))
                {
                    write(tmpnetsocket->socketfd,message,rt+HEADLEN);
                    break;
                }
                tmpnetsocket = tmpnetsocket->next;
            }
            pthread_mutex_unlock(&netsocketmutex);
        }
    }//while recv
    
    pthread_mutex_lock(&netsocketmutex);
    netsocketphead = delnetsocket(netsocketphead,socketfd);
    pthread_mutex_unlock(&netsocketmutex);

    return NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  server part
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  server part

int main(int argc,char *argv[])
{
    int rt;
    int n;
    int len;
    int sourcefile;

    char *tmpfilename;
    char sourcefilename[1024];
    char buf[1024];
    char message[4096];

    struct msghead *phead = (struct msghead *)message;
    
    pthread_t tpid;
    pthread_t transfiletpid;

    int serversocket;
    int acceptsocket;
    
    struct sockaddr_in serverin;

    in_port_t serverport = TCPPORT;

    int destip;

    if(argc >= 2 )
    {
        serverport = atoi(argv[1]);
    }

    pthread_mutex_init(&netsocketmutex,NULL); //////////////////////////////////////////// init mutex
    
    printf("Server Mode:\n");
    serversocket = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == serversocket)
    {
        printf("cannot socket server!\n");
        return -1;
    }

    serverin.sin_family = AF_INET;
    serverin.sin_port = htons(serverport);
    serverin.sin_addr.s_addr = INADDR_ANY;
    memset(serverin.sin_zero,0,8);
    
    rt = bind(serversocket,(struct sockaddr *)&serverin,sizeof(serverin));
    if(-1 == rt)
    {
        printf("cannot bind!\n");
        return -1;
    }

    rt = listen(serversocket,SOMAXCONN);
    if(-1 == rt)
    {
        printf("cannot listen!\n");
        return -1;
    }
    
    pthread_create(&tpid,NULL,tellclientby3sec,(void *)NULL);

    while(1)
    {
        len = sizeof(serverin);
        acceptsocket = accept(serversocket,(struct sockaddr *)&serverin,&len);
        if(-1 == acceptsocket)
        {
            printf("cannot  accept!\n");
            return -1;
        }
        printf("IP:%s is accept!\n",inet_ntoa(serverin.sin_addr));
        
        pthread_mutex_lock(&netsocketmutex);
        netsocketphead = addnetsocket(netsocketphead,acceptsocket);
        pthread_mutex_unlock(&netsocketmutex);
        
        pthread_create(&tpid,NULL,getmessage,(void *)acceptsocket);
    }
    close(serversocket);
    return 0;
}
