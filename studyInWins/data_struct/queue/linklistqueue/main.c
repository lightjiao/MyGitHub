#include <stdio.h>
#include "queue.h"

int main()
{
    struct myqueue q;
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    int e = 50;
    int *p;
    initallqueue(&q);
    q.put(&q,&a);
    q.put(&q,&b);
        p = q.get(&q);
        printf("0x%x,%d\n",p,*p);
    q.put(&q,&c);
    q.put(&q,&d);
    q.put(&q,&e);
        p = q.get(&q);
        printf("0x%x,%d\n",p,*p);
    q.put(&q,&a);
    q.put(&q,&b);
    q.put(&q,&c);
    while(!q.isempty(&q))
    {
        p = q.get(&q);
        printf("0x%x,%d\n",p,*p);
    }
    return 0;
}
