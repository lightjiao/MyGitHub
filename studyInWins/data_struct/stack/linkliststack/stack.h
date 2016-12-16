
#ifndef __STACK_H_
#define __STACK_H_

struct node
{
    void *data;
    struct node *next;
};

struct mystack
{
    struct node *head;
};

extern int initall(struct mystack *s);
extern int push(struct mystack *s,void *data);
extern void* pop(struct mystack *s);
extern void* peek(struct mystack *s);
extern int isempty(struct mystack *s);

#endif
