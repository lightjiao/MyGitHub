
#ifndef __QUEUE_H_
#define __QUEUE_H_

struct queuenode
{
    void *data;
    struct queuenode *pre;
    struct queuenode *next;
};

struct myqueue
{
    struct queuenode *head;
    struct queuenode *tail;
};

extern int initallqueue(struct myqueue *s);
extern int putqueue(struct myqueue *s,void *data);
extern void* getqueue(struct myqueue *s);
extern int queueisempty(struct myqueue *s);
extern void* peekqueue(struct myqueue *s);

#endif
