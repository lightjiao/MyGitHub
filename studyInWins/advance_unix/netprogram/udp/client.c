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
    int clientsocket;
    struct sockaddr_in clientin;
    int clientinlen;
    int destip;

    clientsocket = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == clientsocket)
    {
        printf("cannot socket client!\n");
        return -1;
    }

    printf("Please input the IP you want talk:");
    scanf("%s",buf);
    destip = inet_addr(buf);

    clientin.sin_family = AF_INET;
    clientin.sin_port = htons(3000);
    clientin.sin_addr.s_addr = destip;
    memset(clientin.sin_zero,0,8);

    clientinlen = sizeof(clientin);

    while(1)
    {
        rt = read(STDIN_FILENO,buf,1024);
        sendto(clientsocket,buf,rt,0,(struct sockaddr *)&clientin,clientinlen);
        if(0 == rt)
        {
            break;
        }
    }
}
