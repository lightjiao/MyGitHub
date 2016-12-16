
#ifndef __STACK_H_
#define __STACK_H_

struct mystack
{
    void **data;
    unsigned int space;
    unsigned int top;
};

extern int initall(struct mystack*);
extern int push(struct mystack*,void*);
extern void* pop(struct mystack*);
extern int isempty(struct mystack*);
extern void* peek(struct mystack*);

#endif
