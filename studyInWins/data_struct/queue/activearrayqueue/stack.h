
#ifndef __STACK_H_
#define __STACK_H_

struct mystack
{
    void **data;
    int head;
    int tail;
    unsigned int space;
};

extern int initall(struct mystack*);
extern int push(struct mystack*,void*);
extern void* pop(struct mystack*);
extern int isempty(struct mystack*);
extern void* peek(struct mystack*);

#endif
