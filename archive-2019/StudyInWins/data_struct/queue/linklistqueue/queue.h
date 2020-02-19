
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
    int (*isempty)(struct myqueue *);
    int (*put)(struct myqueue *,void *data);
    void *(*get)(struct myqueue *);
    void *(*peek)(struct myqueue *);
};

extern int initallqueue(struct myqueue *s);

#endif
