#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int isempty(struct mystack *s)
{
    return s->head == s->tail;
}

void* peek(struct mystack *s)
{
    if(isempty(s))
    {
        return NULL;
    }
    return s->data[(s->head+s->space-1)%(s->space)];
}

static int increase(struct mystack *s)
{
    void **p;
    int len;
    p = malloc(s->space*2*sizeof(void*));
    if(NULL == p)
    {
        return -1;
    }
    len = (s->head + s->space - s->tail) % s->space;
    
    if(s->tail < s->head)
    {
        memcpy(p,&s->data[s->tail],len*sizeof(void*));
    }
    else
    {
        memcpy(p,&s->data[s->tail],(s->space-s->tail)*sizeof(void*));
        memcpy(&p[s->space-s->tail],s->data,s->head*sizeof(void*));
    }
    free(s->data);
    s->data = p;
    s->space *= 2;
    s->tail = 0;
    s->head = len;
    return 0;
}

int initall(struct mystack *s)
{
    s->space = 4;
    s->data = malloc(s->space*sizeof(void*));
    if(NULL == s->data)
    {
        return -1;
    }
    s->head = s->tail = 0;
    return 0;
}

int push(struct mystack *s,void *data)
{
    if((s->head+1)%s->space == s->tail)
    {
        if(increase(s))
        {
            return -1;
        }
    }
    s->data[s->head] = data;
    s->head = (s->head+1) % s->space;
    return 0;
}

void* pop(struct mystack *s)
{
    int tmp;
    if(isempty(s))
    {
        return NULL;
    }
    tmp = s->tail;
    s->tail = (s->tail+1) % s->space;
    return s->data[tmp];
}

