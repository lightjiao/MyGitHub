#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int isempty(struct mystack *s)
{
    return 0 == s->top;
}

void* peek(struct mystack *s)
{
    if(isempty(s))
    {
        return NULL;
    }
    return s->data[s->top-1];
}

static int increase(struct mystack *s)
{
    void **p;
    p = malloc(s->space*2*sizeof(void*));
    if(NULL == p)
    {
        return -1;
    }
    s->space *= 2;
    memcpy(p,s->data,s->top*sizeof(void*));
    free(s->data);
    s->data = p;
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
    s->top = 0;
    return 0;
}

int push(struct mystack *s,void *data)
{
    if(s->top == s->space)
    {
        if(increase(s))
        {
            return -1;
        }
    }
    s->data[s->top] = data;
    s->top++;
    return 0;
}

void* pop(struct mystack *s)
{
    if(isempty(s))
    {
        return NULL;
    }
    s->top--;
    return s->data[s->top];
}

