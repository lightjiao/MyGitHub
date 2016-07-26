#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

int queueisempty(struct myqueue *s)
{
    return NULL == s->head;
}

void* peekqueue(struct myqueue *s)
{
    if(queueisempty(s))
    {
        return NULL;
    }
    return s->head->data;
}

int initallqueue(struct myqueue *s)
{
    s->head = NULL;
    s->tail = NULL;
    return 0;
}

int putqueue(struct myqueue *s,void *data)
{
    struct queuenode *pnode;
    pnode = malloc(sizeof(struct queuenode));
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

void* getqueue(struct myqueue *s)
{
    struct queuenode *tail;
    void *data;
    if(queueisempty(s))
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

