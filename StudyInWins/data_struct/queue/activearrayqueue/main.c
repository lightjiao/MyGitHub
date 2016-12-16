#include <stdio.h>
#include "stack.h"

int main()
{
    struct mystack s;
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    int e = 50;
    int *p;
    initall(&s);
    push(&s,&a);
    push(&s,&b);
        p = pop(&s);
        printf("0x%x,%d\n",p,*p);
    push(&s,&c);
    push(&s,&d);
    push(&s,&e);
        p = pop(&s);
        printf("0x%x,%d\n",p,*p);
    push(&s,&a);
    push(&s,&b);
        p = pop(&s);
        printf("0x%x,%d\n",p,*p);
    push(&s,&c);
    push(&s,&d);
    push(&s,&e);
        p = pop(&s);
        printf("0x%x,%d\n",p,*p);
    while(!isempty(&s))
    {
        p = pop(&s);
        printf("0x%x,%d\n",p,*p);
    }
    return 0;
}
