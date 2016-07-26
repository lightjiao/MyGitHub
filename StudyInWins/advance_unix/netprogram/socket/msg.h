
#ifndef __MSG_H__
#define __MSG_H__

struct msghead
{
    unsigned int type;
    unsigned int msglen;
};

enum
{
    TALK_MESSAGE = 0,
    START_TRANS_FILE,
    TRANS_FILE,
    END_TRANS_FILE,
};

#define HEADLEN sizeof(struct msghead)

#endif

