#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "msg.h"


struct fortransfile
{
    int socket;
    int file;
    char sourcename[20];
    char destname[20];
};

int getType(char *buf)
{
    char *p;
    int n;
    
    p = strchr(buf,':');
    if(NULL == p)
    {
        return TALK_MESSAGE;
    }
    
    if(buf[0] == 't')
    {
        return SINGLE_TALK_MESSAGE;
    }

    else if(buf[0] == 'f')
    {
        if(NULL == strchr(p+1,':'))
        {
            return START_TRANS_FILE;
        }

        return SINGLE_START_TRANS_FILE;
    }

    else if(buf[0] == 'l')
    {
        return WHO_IS_ONLINE;
    }

    return WRONG_TYPE;
}


void* sendfile(void *arg)
{
    int rt;
    int sourcefile;
    int socketfd;
    char message[4096];
    char destname[20];
    int single_trans_file;
    struct fortransfile *p;

    struct msghead *phead = (struct msghead *)message;

    p = malloc(sizeof(struct fortransfile));
    memcpy(p,arg,sizeof(struct fortransfile));

    socketfd = p->socket;
    sourcefile = p->file;
    single_trans_file = strlen(p->destname);
    strcpy(phead->destname,p->destname);
    strcpy(phead->sourcename,p->sourcename);

    while(1)
    {
        rt = read(sourcefile,message+HEADLEN,4096-HEADLEN);
        phead->msglen = htonl(rt);
        if(0 == rt)
        {
            if(single_trans_file)
            {
                phead->type = htonl(SINGLE_END_TRANS_FILE);
            }
            else
            {
                phead->type = htonl(END_TRANS_FILE);
            }
            rt = 2048;
            phead->msglen = htonl(rt);
            send(socketfd,message,rt+HEADLEN,0);
            close(sourcefile);
            free(p);
            break;
        }
        if(single_trans_file)
        {
            phead->type = htonl(SINGLE_TRANS_FILE);
        }
        else
        {
            phead->type = htonl(TRANS_FILE);
        }
        send(socketfd,message,rt+HEADLEN,0);
    }
    return NULL;
}

int autosavefilefd(void)
{
    int savefilefd = -1;
    char savefilename[20];
    strcpy(savefilename,"Savefile0");
    while(1)
    {
        savefilefd = open(savefilename,O_WRONLY|O_CREAT|O_EXCL,0666);
        if(savefilefd > 0)
        {
            return savefilefd;
        }
        savefilename[strlen(savefilename)-1] += 1;
    }
}

void* getmessage(void *arg)
{
    int rt;
    int socketfd;
    int savefile;
    char buf[1024];
    char message[4096];
    int type;
    int msglen;
    char sourcename[20];

    struct msghead *phead = (struct msghead *)message;

    socketfd = (int)arg;

    while(1)
    {
        recv(socketfd,phead,HEADLEN,MSG_WAITALL);
        type = ntohl(phead->type);
        msglen = ntohl(phead->msglen);
        strcpy(sourcename,phead->sourcename);
        
        if((TALK_MESSAGE == type)||(SINGLE_TALK_MESSAGE == type))
        {
            rt = recv(socketfd,message,msglen,MSG_WAITALL);
            if(0 == rt)
            {
                break;
            }
            write(STDOUT_FILENO,sourcename,strlen(sourcename));
            if(SINGLE_TALK_MESSAGE == type)
            {
                write(STDOUT_FILENO," to you:",8);
            }
            else
            {
                write(STDOUT_FILENO," to all:",8);
            }
            write(STDOUT_FILENO,message,msglen);
        }
        else if((START_TRANS_FILE == type)||(SINGLE_START_TRANS_FILE == type))
        {
            rt = recv(socketfd,message,msglen,MSG_WAITALL);
            savefile = autosavefilefd();
            write(STDOUT_FILENO,"Trans file from ",16);
            write(STDOUT_FILENO,sourcename,strlen(sourcename));
            if(START_TRANS_FILE == type)
            {
                write(STDOUT_FILENO," to all start!\n",15);
            }
            else
            {
                write(STDOUT_FILENO," to you start!\n",15);
            }
        }
        else if((TRANS_FILE == type)||(SINGLE_TRANS_FILE == type))
        {
            rt = recv(socketfd,message,msglen,MSG_WAITALL);
            write(savefile,message,rt);
        }
        else if((END_TRANS_FILE == type)||(SINGLE_END_TRANS_FILE == type))
        {
            recv(socketfd,message,msglen,MSG_WAITALL);
            write(STDOUT_FILENO,"Trans file from ",16);
            write(STDOUT_FILENO,sourcename,strlen(sourcename));
            if(END_TRANS_FILE == type)
            {
                write(STDOUT_FILENO," to all complete!\n",18);
            }
            else
            {
                write(STDOUT_FILENO," to you complete!\n",18);
            }
            close(savefile);
        }
    }
    return NULL;
}


///////////////////////////////////////////////// client part 

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

    char myname[20];
    char *tmpdestname;
    char *tmpdestnameend;
    char destname[20];

    struct msghead *phead = (struct msghead *)message;
    struct udpmsghead *udpmsgphead = (struct udpmsghead *)message;

    pthread_t tpid;
    pthread_t transfiletpid;

    int clientsocket;
    int udpclientsocket;
    int val = 1;

    struct sockaddr_in clientin;
    struct sockaddr_in udpclientin;

    struct fortransfile ftransfile;

    printf("Client Mode:\n");

    udpclientsocket = socket(AF_INET,SOCK_DGRAM,0);////////////////////// a UDP socket
    if(-1 == udpclientsocket)
    {
        printf("cannot socket udpclient!\n");
        return -1;
    }

    ////////////////////////////////////////////////////////////////////// prepare for broadcast to know where server is

    udpclientin.sin_family = AF_INET;
    udpclientin.sin_port = htons(UDPPORT);
    udpclientin.sin_addr.s_addr = inet_addr("192.168.1.255");
    memset(udpclientin.sin_zero,0,8);

    rt = setsockopt(udpclientsocket,SOL_SOCKET,SO_BROADCAST,&val,sizeof(udpclientin));
    if(-1 == rt)
    {
        printf("cannot set client udp!\n");
        return -1;
    }

    udpmsgphead->type = htonl(CLIENT_BROADCAST_REQUEST);

    sendto(udpclientsocket,message,4,0,(struct sockaddr *)&udpclientin,sizeof(udpclientin));

    ///////////////////////////////////////////////////////////////////// prepare for recv respons from server where he is
    
    udpclientin.sin_addr.s_addr = INADDR_ANY;

    rt = bind(udpclientsocket,(struct sockaddr *)&udpclientin,sizeof(udpclientin));
    if(-1 == rt)
    {
        printf("cannot bind udp!\n");
        return -1;
    }

    len = sizeof(udpclientin);

    while(1)
    {
        rt = recvfrom(udpclientsocket,message,10,0,(struct sockaddr *)&udpclientin,&len);
        if(udpmsgphead->type = htonl(SERVER_BROADCAST_RESPONS))
        {
            break;
        }
    }

    //////////////////////////////////////////////////////////////////// prepare for TCP part

    clientsocket = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == clientsocket)
    {
        printf("cannot socket cilent!\n");
        return -1;
    }

    clientin.sin_family = AF_INET;
    clientin.sin_port = udpmsgphead->port;
    clientin.sin_addr.s_addr = udpmsgphead->ip;
    memset(clientin.sin_zero,0,8);

    rt = connect(clientsocket,(struct sockaddr *)&clientin,sizeof(clientin));
    if(-1 == rt)
    {
        printf("cannot connect!\n");
        return -1;
    }

    printf("Please input your chatname:");
    while(1)
    {
        scanf("%s",myname);
        fgets(buf,1024,stdin);

        phead->type = htonl(WHO_AM_I);
        strcpy(phead->sourcename,myname);

        write(clientsocket,message,HEADLEN);
        recv(clientsocket,message,HEADLEN,MSG_WAITALL);
        if(NAME_SUCCESSFUL == ntohl(phead->type))
        {
            break;
        }
        printf("Name reapeat,Please input a new chatname:");
    }

    pthread_create(&tpid,NULL,getmessage,(void *)clientsocket);

    while(1)
    {
        rt = read(STDIN_FILENO,buf,1024);
        buf[rt] = 0;
        n = getType(buf);
        
        if(WRONG_TYPE == n)
        {
            write(STDOUT_FILENO,"wrong message type!\n",20);
            continue;
        }

        else if(START_TRANS_FILE == n)
        {
            buf[rt-1] = 0;
            tmpfilename = strchr(buf,':');
            tmpfilename++;
            strcpy(sourcefilename,tmpfilename);
            sourcefile = open(sourcefilename,O_RDONLY);
            if(-1 == sourcefile)
            {
                printf("cannot open file %s!\n",sourcefilename);
                continue;
            }

            phead->type = htonl(START_TRANS_FILE);
            phead->msglen = 0;
            strcpy(phead->sourcename,myname);
            write(clientsocket,message,HEADLEN);
            
            ftransfile.socket = clientsocket;
            ftransfile.file = sourcefile;
            ftransfile.destname[0] = 0;
            strcpy(ftransfile.sourcename,myname);

            pthread_create(&transfiletpid,NULL,sendfile,(void *)&ftransfile);
            continue;
        }

        else if(SINGLE_START_TRANS_FILE == n)
        {
            buf[rt-1] = 0;
            tmpdestname = strchr(buf,':');
            tmpdestname++;
            tmpdestnameend = strchr(tmpdestname,':');
            memcpy(destname,tmpdestname,tmpdestnameend - tmpdestname);
            destname[tmpdestnameend-tmpdestname+1] = 0;
           
            tmpfilename = tmpdestnameend+1;
            strcpy(sourcefilename,tmpfilename);
            sourcefile = open(sourcefilename,O_RDONLY);
            if(-1 == sourcefile)
            {
                printf("cannot open file %s!\n",sourcefilename);
                continue;
            }
            
            phead->type = htonl(SINGLE_START_TRANS_FILE);
            phead->msglen = 0;
            strcpy(phead->destname,destname);
            strcpy(phead->sourcename,myname);
            write(clientsocket,message,HEADLEN);
            
            ftransfile.socket = clientsocket;
            ftransfile.file = sourcefile;
            strcpy(ftransfile.sourcename,myname);
            strcpy(ftransfile.destname,destname);

            pthread_create(&transfiletpid,NULL,sendfile,(void *)&ftransfile);
            continue;
        }
        
        else if(SINGLE_TALK_MESSAGE == n)
        {
            tmpdestname = strchr(buf,':');
            tmpdestname++;
            tmpdestnameend = strchr(tmpdestname,':');
            memcpy(destname,tmpdestname,tmpdestnameend - tmpdestname);
            destname[tmpdestnameend-tmpdestname+1] = 0;
            
            phead->type = htonl(SINGLE_TALK_MESSAGE);
            strcpy(phead->destname,destname);
            rt = rt - (tmpdestnameend - buf) - 1;
            memcpy(message+HEADLEN,tmpdestnameend+1,rt);
            
            phead->msglen = htonl(rt);
        }
        else if(TALK_MESSAGE == n)
        {
            phead->type = htonl(TALK_MESSAGE);
            phead->msglen = htonl(rt);
            memcpy(message+HEADLEN,buf,rt);
            phead->destname[0] = 0;
        }
        else if(WHO_IS_ONLINE == n)
        {
            phead->type = htonl(WHO_IS_ONLINE);
            strcpy(phead->sourcename,myname);
            phead->msglen = htonl(2048);
            write(clientsocket,message,2048+HEADLEN);
            continue;
        }

        strcpy(phead->sourcename,myname);
        write(clientsocket,message,rt+HEADLEN);
        if(0 == rt)
        {
            break;
        }
    }
    close(clientsocket);
    return 0;
}
