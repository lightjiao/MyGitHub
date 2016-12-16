#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char **argv)
{
    int rt;
    char buf[1024];
    char message[4096];
    int serversocket;
    struct sockaddr_in serverin;
    int serverinlen;
    
    serversocket = socket(AF_INET,SOCK_DGRAM,0); // SOCK_DGRAM for udp ,like writing a letter // tcp like a phonecall
    if(-1 == serversocket)
    {
        printf("cannot socket server!\n");
        return -1;
    }

    serverin.sin_family = AF_INET;
    serverin.sin_port = htons(3000);
    serverin.sin_addr.s_addr = INADDR_ANY;
    memset(serverin.sin_zero,0,8);
    
    serverinlen = sizeof(serverin);

    rt = bind(serversocket,(struct sockaddr *)&serverin,serverinlen);
    if(-1 == rt)
    {
        printf("cannot bind!\n");
        close(serversocket);
        return -1;
    }

    while(1)
    {
        rt = recvfrom(serversocket,buf,1024,0,(struct sockaddr *)&serverin,&serverinlen);
        if(0 == rt)
        {
            break;
        }
        printf("IP:%s,Port:%d\n",inet_ntoa(serverin.sin_addr),ntohs(serverin.sin_port));
        write(STDOUT_FILENO,buf,rt);
    }

}


