
#include "list.h"

int add_list_pre(struct list *pos,struct list *lt)
{
    pos->pre->next = lt;
    lt->pre = pos->pre;
    lt->next = pos;
    pos->pre = lt;

    return;
}

int add_list_next(struct list *pos,struct list *lt)
{
    pos->next->pre = lt;
    lt->next = pos->next;
    lt->pre = pos;
    pos->next = lt;

    return;
}

int del_list(struct list *pos)
{
    pos->next->pre = pos->pre;
    pos->pre->next = pos->next;

    return;
}
