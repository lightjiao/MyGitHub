#ifndef __MSG_H__
#define __MSG_H__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define UDPPORT 3333
#define TCPPORT 2222


struct msghead
{
    unsigned short trstype;
    unsigned short msgtype;
    unsigned int   msglen;
    char msgtime[20];
    char destname[20];
    char sourcename[20];
};

#define HEADLEN sizeof(struct msghead)

struct udpmsghead
{
    unsigned int msgtype;
    unsigned int ip;
    unsigned int port;
};

enum
{
    CHATNAME_REG = 0,
    CHATNAME_REPEAT,
    CHATNAME_SUCCESSFUL,
    CHATNAME_NOTEXIST,
    PASSWORD_WRONG,
    WHO_IS_ONLINE,
    LOG_IN,
    LOG_OUT,
    ////////////////////////////////
    BROADCAST,
    SINGLE,
    ////////////////////////////////
    TALK_MSG,
    FILE_START,
    FILE_TRANS,
    FILE_END,
    USER_LOG_IN,
    USER_LOG_OUT,
    ////////////////////////////////
};

enum
{
    S_BROADCAST_RES = 0,
    S_SINGLE_RES,
    C_BROADCAST_REQ,
    C_SINGLE_REQ,
};


#endif
