
#ifndef __MSG_H__
#define __MSG_H__

struct msghead
{
    unsigned int type;
    unsigned int msglen;
    char destname[20];
    char sourcename[20];
};

struct udpmsghead
{
    unsigned int type;
    unsigned int ip;
    unsigned short port;
};

enum
{
    WHO_AM_I = 0,
    NAME_REPEAT,
    NAME_SUCCESSFUL,
    WHO_IS_ONLINE,

    //////////////////////////////////////
    
    TALK_MESSAGE,
    START_TRANS_FILE,
    TRANS_FILE,
    END_TRANS_FILE,

    //////////////////////////////////////
 
    SINGLE_TALK_MESSAGE,
    SINGLE_START_TRANS_FILE,
    SINGLE_TRANS_FILE,
    SINGLE_END_TRANS_FILE,
    
    //////////////////////////////////////

    LOG_OUT,
    WRONG_TYPE,
};

enum
{
    SERVER_BROADCAST_RESPONS = 0,
    SERVER_SINGLE_RESPONS,
    CLIENT_BROADCAST_REQUEST,
    CLIENT_SINGLE_REQUEST,
};

#define HEADLEN sizeof(struct msghead)
#define UDPPORT 8888
#define TCPPORT 2000

#endif

