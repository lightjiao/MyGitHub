#include <stdio.h>
#include <string.h>
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
    
    return START_TRANS_FILE;
}

void* sendfile(void *arg)
{
    int rt;
    int sourcefile;
    int socketfd;
    char message[4096];
    struct fortransfile *p;
    struct msghead *phead = (struct msghead *)message;

    p = (struct fortransfile *)arg;

    socketfd = p->socket;
    sourcefile = p->file;
    
    while(1)
    {
        rt = read(sourcefile,message+HEADLEN,4096-HEADLEN);
        if(0 == rt)
        {
            phead->type = htonl(END_TRANS_FILE);
            phead->msglen = htonl(rt);
            write(socketfd,message,rt+8);
            close(sourcefile);
            break;
        }
        phead->type = htonl(TRANS_FILE);
        phead->msglen = htonl(rt);
        write(socketfd,message,rt+HEADLEN);
    }
    return NULL;
}

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

    struct msghead *phead = (struct msghead *)message;

    socketfd = *(int *)arg;

    while(1)
    {
        recv(socketfd,phead,HEADLEN,MSG_WAITALL);
        type = ntohl(phead->type);
        msglen = ntohl(phead->msglen);

        if(TALK_MESSAGE == type)
        {
            rt = recv(socketfd,message,msglen,MSG_WAITALL);
            if(0 == rt)
            {
                break;
            }
            write(STDOUT_FILENO,"recv:",5);
            write(STDOUT_FILENO,message,msglen);
        }
        if(START_TRANS_FILE == type)
        {
            
            rt = recv(socketfd,message,msglen,MSG_WAITALL);

            savefile = open("savefile",O_WRONLY|O_CREAT|O_EXCL,0666);
            if(-1 == savefile)
            {
                printf("cannot open savefile or it's already exist!\n");
            }
            savefileflag = 1;
        }
        if(TRANS_FILE == type)
        {
            if(0 == savefileflag)
            {
                continue;
            }
            rt = recv(socketfd,message,msglen,MSG_WAITALL);
            write(savefile,message,rt);
        }
        if(END_TRANS_FILE == type)
        {
            if(0 == savefileflag)
            {
                continue;
            }
            close(savefile);
            printf("Trans file complete!\n");
        }
    }
    return NULL;
}


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
    int clientsocket;
    
    struct sockaddr_in serverin;
    struct sockaddr_in clientin;

    in_port_t serverport = 2000;
    in_port_t clientport = 2000;

    int destip;
    
    struct fortransfile ftransfile;

    if(argc < 2)
    {
    	printf("too little argc!\n");
    	return -1;
    }

    if(0 == strcmp(argv[1],"server"))
    {
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

        while(1)
        {
            len = sizeof(serverin);
            acceptsocket = accept(serversocket,(struct sockaddr *)&serverin,&len);
            if(-1 == acceptsocket)
            {
                printf("cannot  accept!\n");
                return -1;
            }
            printf("IP:%s Port:%d\n",inet_ntoa(serverin.sin_addr),ntohs(serverin.sin_port));
            
            pthread_create(&tpid,NULL,getmessage,(void *)&acceptsocket);
            while(1)
            {
                rt = read(STDIN_FILENO,buf,1024);
                buf[rt] = 0;
                n = getType(buf);
        
                if(START_TRANS_FILE == n)
                {
                    buf[rt-1] = 0;
                    tmpfilename = strchr(buf,':');
                    tmpfilename++;
                    strcpy(sourcefilename,tmpfilename);
                    sourcefile = open(sourcefilename,O_RDONLY);
                    if(-1 == sourcefile)
                    {
                        printf("cannot open file or it's not exist!\n");
                        continue;
                    }

                    memcpy(message+HEADLEN,buf,rt);
                    phead->type = htonl(START_TRANS_FILE);
                    phead->msglen = htonl(rt);
                    write(acceptsocket,message,rt+HEADLEN);
                    
                    ftransfile.socket = acceptsocket;
                    ftransfile.file = sourcefile;

                    pthread_create(&transfiletpid,NULL,sendfile,(void *)&ftransfile);
                    continue;
                }
                memcpy(message+HEADLEN,buf,rt);
                phead->type = htonl(TALK_MESSAGE);
                phead->msglen = htonl(rt);
                write(acceptsocket,message,rt+HEADLEN);
                if(0 == rt)
                {
                    break;
                }
            }
            pthread_join(tpid,NULL);
            close(acceptsocket);
        }
        close(serversocket);
    }

    
    /////////////////////////////////////////////////////////////////////////  client part
    
    else if(0 == strcmp(argv[1],"client"))
    {
 		printf("Client Mode:\n");
 		printf("Please input the IP and Port you want connect:");
 		scanf("%s,%d",buf,&clientport);

        destip = inet_addr(buf);

        clientsocket = socket(AF_INET,SOCK_STREAM,0);
        if(-1 == clientsocket)
        {
            printf("cannot socket cilent!\n");
            return -1;
        }

        clientin.sin_family = AF_INET;
        clientin.sin_port = htons(clientport);
        clientin.sin_addr.s_addr = destip;
        memset(clientin.sin_zero,0,8);

        rt = connect(clientsocket,(struct sockaddr *)&clientin,sizeof(clientin));
        if(-1 == rt)
        {
            printf("cannot connect!\n");
            return -1;
        }

        pthread_create(&tpid,NULL,getmessage,(void *)&clientsocket);

        while(1)
        {
            rt = read(STDIN_FILENO,buf,1024);
            buf[rt] = 0;
            n = getType(buf);

            if(START_TRANS_FILE == n)
            {
                buf[rt-1] = 0;
                tmpfilename = strchr(buf,':');
                tmpfilename++;
                strcpy(sourcefilename,tmpfilename);
                sourcefile = open(sourcefilename,O_RDONLY);
                if(-1 == sourcefile)
                {
                    printf("cannot open file or it's not exist!\n");
                    continue;
                }

                memcpy(message+HEADLEN,buf,rt);
                phead->type = htonl(START_TRANS_FILE);
                phead->msglen = htonl(rt);
                write(clientsocket,message,rt+HEADLEN);
                
                ftransfile.socket = clientsocket;
                ftransfile.file = sourcefile;

                pthread_create(&transfiletpid,NULL,sendfile,(void *)&ftransfile);
                continue;
            }
            memcpy(message+HEADLEN,buf,rt);
            phead->type = htonl(TALK_MESSAGE);
            phead->msglen = htonl(rt);
            write(clientsocket,message,rt+HEADLEN);
            if(0 == rt)
            {
                break;
            }
        }
        pthread_join(tpid,NULL);
        close(clientsocket);
    }
    else
    {
 		printf("please input 'server' or 'client'!\n");
 		return -1;
    }
}
