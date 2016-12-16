#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <linux/sockios.h>
#include <linux/ioctl.h>

#include <features.h> // the glibc
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h> // protcole of lianluceng(L2)
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h> // protcole of lianluceng
#endif


struct arphead
{
    short htype;
    short ptype;
    char  hsize;
    char  psize;
    short opcode;
    char  srcmac[6];
    char  srcip[4];
    char  dstmac[6];
    char  dstip[4];
};


int getIndex(int sfd,char *name)
{
    struct ifreq ifr;
    memset(&ifr,0,sizeof(ifr));
    strcpy(ifr.ifr_name,name);

    if(ioctl(sfd,SIOCGIFINDEX,&ifr) < 0)
    {
        printf("ioctl() failed to get index %s\n",name);
        return -1;
    }

    return ifr.ifr_ifindex;
}


int main(int argc,char **argv)
{
    int sfd;
    int i = 0;
    int n;
    int rt;
    struct sockaddr_ll ll;
    int len = sizeof(ll);

    char recvarppack[2000];
    char arppack[64] = {0};
    struct arphead *arph = (struct arphead *)(arppack+14);
    struct arphead *recvarph = (struct arphead *)(recvarppack+14);

    int sip = inet_addr("192.169.100.2");
    char smac[6] = {0,0x0c,0x29,0xa6,0xcd,0x54};
    
    ///////////////////////////////////////// make arp pack
    
    memcpy(arppack+6,smac,6);
    arppack[12] = 0x8;
    arppack[13] = 0x06;
    arph->htype = htons(1);
    arph->ptype = htons(0x0800);
    arph->hsize = 6;
    arph->psize = 4;
    arph->opcode = htons(2);
    memcpy(arph->srcmac,smac,6);
    memcpy(arph->srcip,(void *)&sip,4);
    
    ///////////////////////////////////////////////////////

    sfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(-1 == sfd)
    {
        printf("cannot socket!\n");
        return -1;
    }
    memset(&ll,0,len);
    ll.sll_family = PF_PACKET;
    ll.sll_ifindex = getIndex(sfd,"eth0");

    while(1)
    {
        rt = recvfrom(sfd,recvarppack,2000,0,(struct sockaddr *)&ll,&len);
        if(recvarph->opcode == ntohs(1))
        {
            if(0 == memcmp(recvarph->dstip,(char *)&sip,4))
            {
                memcpy(arppack,recvarppack+6,6);
                memcpy(arph->dstmac,recvarph->srcmac,6);
                memcpy(arph->dstip,recvarph->srcip,4);
                sendto(sfd,arppack,64,0,(struct sockaddr *)&ll,len);
                sendto(sfd,arppack,64,0,(struct sockaddr *)&ll,len);
                sendto(sfd,arppack,64,0,(struct sockaddr *)&ll,len);
            }
        }
    }

    close(sfd);
    return 0;
}











