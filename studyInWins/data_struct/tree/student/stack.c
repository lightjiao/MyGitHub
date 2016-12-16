#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int stackisempty(struct mystack *s)
{
    return NULL == s->head;
}

int initallstack(struct mystack *s)
{
    s->head = NULL;
    return 0;
}

void* peekstack(struct mystack *s)
{
    if(stackisempty(s))
    {
        return NULL;
    }
    return s->head->data;
}

static struct stacknode* inserthead(struct stacknode *head,struct stacknode *pnode)
{
    pnode->next = head;
    return pnode;
}

int pushstack(struct mystack *s,void *data)
{
    struct stacknode *pnode;
    pnode = malloc(sizeof(struct stacknode));
    if(NULL == pnode)
    {
        return -1;
    }
    pnode->data = data;
    s->head = inserthead(s->head,pnode);
    return 0;
}

static struct stacknode* delhead(struct stacknode *head)
{
    head = head->next;
    return head;
}

void* popstack(struct mystack *s)
{
    void *data;
    struct stacknode *p = NULL;
    if(stackisempty(s))
    {
        return NULL;
    }
    p = s->head;
    s->head = delhead(s->head);
    data = p->data;
    free(p);
    return data;
}

