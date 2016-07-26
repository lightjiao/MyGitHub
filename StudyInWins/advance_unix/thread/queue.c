#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"


static int isempty(struct myqueue *s)
{
    return NULL == s->head;
}

static void* peek(struct myqueue *s)
{
    if(s->isempty(s))
    {
        return NULL;
    }
    return s->head->data;
}

static int put(struct myqueue *s,void *data)
{
    struct node *pnode;
    pnode = malloc(sizeof(struct node));
    if(NULL == pnode)
    {
        return -1;
    }
    
    pnode->data = data;
    pnode->next = pnode->pre = NULL;
    
    pnode->next = s->head;
    if(NULL != s->head)
    {
        s->head->pre = pnode;
    }
    s->head = pnode;
    
    if(NULL == s->tail)
    {
        s->tail = pnode;
    }
    return 0;
}

static void* get(struct myqueue *s)
{
    struct node *tail;
    void *data;
    if(s->isempty(s))
    {
        return NULL;
    }
    
    tail = s->tail;
    data = tail->data;

    if(NULL != tail->pre)
    {
        s->tail->pre->next = NULL;
        s->tail = tail->pre;
    }
    else
    {
        s->head = NULL;
        s->tail = NULL;
    }
    free(tail);
    return data;
}

int initallqueue(struct myqueue *s)
{
    s->head = NULL;
    s->tail = NULL;
    s->get = get;
    s->put = put;
    s->isempty = isempty;
    s->peek = peek;
    return 0;
}
