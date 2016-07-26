#include <stdio.h>
#include "stack.h"

int main()
{
    struct mystack s;
    int a = 10;
    int b = 20;
    int c = 30;
    int *p;
    initall(&s);
    printf("&a:0x%x\n&b:0x%x\n&c:0x%x\n",&a,&b,&c);
    push(&s,&a);
    push(&s,&b);
    push(&s,&c);
    while(!isempty(&s))
    {
        p = pop(&s);
        printf("0x%x,%d\n",p,*p);
    }
    return 0;
}
