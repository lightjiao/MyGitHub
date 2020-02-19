#ifndef __LIST_H__
#define __LIST_H__

struct list
{
    struct list *pre;
    struct list *next;
};

#define offset(type,member)   \
    ((unsigned int)&((type *)0)->member)

#define list_for_each(pos,head)    \
    for(pos=(head)->next;pos!=(head);pos=pos->next)

#define list_for_each_prev(pos,head)    \
    for(pos=(head)->pre;pos!=(head);pos=pos->pre)

#define container_of(ptr,type,member)   \
    ((type *)(((unsigned int)ptr)-((unsigned int)offset(type,member))))
 
#endif
