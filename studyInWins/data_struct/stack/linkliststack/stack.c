#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int isempty(struct mystack *s)
{
    return NULL == s->head;
}

int initall(struct mystack *s)
{
    s->head = NULL;
    return 0;
}

void* peek(struct mystack *s)
{
    if(isempty(s))
    {
        return NULL;
    }
    return s->head->data;
}

static struct node* inserthead(struct node *head,struct node *pnode)
{
    pnode->next = head;
    return pnode;
}

int push(struct mystack *s,void *data)
{
    struct node *pnode;
    pnode = malloc(sizeof(struct node));
    if(NULL == pnode)
    {
        return -1;
    }
    pnode->data = data;
    s->head = inserthead(s->head,pnode);
    return 0;
}

static struct node* delhead(struct node *head)
{
    head = head->next;
    return head;
}

void* pop(struct mystack *s)
{
    void *data;
    struct node *p = NULL;
    if(isempty(s))
    {
        return NULL;
    }
    p = s->head;
    s->head = delhead(s->head);
    data = p->data;
    free(p);
    return data;
}

