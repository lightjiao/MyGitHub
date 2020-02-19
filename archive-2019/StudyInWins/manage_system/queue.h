
#ifndef __STACK_H_
#define __STACK_H_

struct node
{
    void *data;
    struct node *pre;
    struct node *next;
};

struct myqueue
{
    struct node *head;
    struct node *tail;
};

extern int initallqueue(struct myqueue *s);
extern int putqueue(struct myqueue *s,void *data);
extern void* getqueue(struct myqueue *s);
extern int queueisempty(struct myqueue *s);
extern void* peekqueue(struct myqueue *s);

#endif
