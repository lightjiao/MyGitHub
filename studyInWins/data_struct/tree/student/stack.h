
#ifndef __STACK_H_
#define __STACK_H_

struct stacknode
{
    void *data;
    struct stacknode *next;
};

struct mystack
{
    struct stacknode *head;
};

extern int initallstack(struct mystack *s);
extern int pushstack(struct mystack *s,void *data);
extern void* popstack(struct mystack *s);
extern void* peekstack(struct mystack *s);
extern int stackisempty(struct mystack *s);

#endif
