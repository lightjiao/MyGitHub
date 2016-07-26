#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//extern void showarray(int*,int);

typedef struct pnumber
{
    int *p;
    unsigned int space;
    unsigned int num;
    unsigned int maxprinum;
}Pstuct;

int _isprime(int a,struct pnumber *b)
{
    int i;
    int s;
    s = (int) sqrt(a);
    for(i=0;(i < b->num) && (b->p[i]<=s);i++)
    {
        if(0 == a % b->p[i])
        {
            return 0;
        }
    }
    return 1;
}

struct pnumber* space_increase(struct pnumber *p)
{
    int i;
    int *temp = NULL;

    temp = malloc(2*p->space*sizeof(int));
    if(NULL == temp)
    {
        printf("malloc fail!\n");
        return;
    }
    p->space = p->space * 2;
    
    for(i=0;i<p->num;i++)
    {
        temp[i] = p->p[i];
    }
    free(p->p);
    p->p = temp;
    return p;
}

int fill_prime(int n,struct pnumber *a)
{
    int i;
    int s = sqrt(n);
    for(i=3;i<=s;i+=2)
    {
        if(_isprime(i,a))
        {
            if(a->num == a->space)
            {
                a = space_increase(a);
            }
            a->p[a->num] = i;
            a->num++;
        }
    }
    a->maxprinum = n;
}

int is_prime(int a,struct pnumber *b)
{
    if(a > b->maxprinum)
    {
        fill_prime(a,b);
    }
    
    return _isprime(a,b);
}


int initall(struct pnumber *a)
{
    a->space = 1;
    a->p = malloc(a->space*sizeof(int));
    if(NULL == a->p)
    {
        a->space = 0;
        return -1;
    }
    a->p[0] = 2;
    a->maxprinum = 3;
    a->num = 1;
    return 0;
}

void judge_pri(void)
{
    int num;
    struct pnumber p;
    initall(&p);

    printf("input a number to judge prime:");
    scanf("%d",&num);
    if(is_prime(num,&p))
    {
        printf("%d is prime number!\n",num);
    }
    else
    {
        printf("%d is not prime number!\n",num);
    }
    return;
}

void solve_to_pri(int n)
{
    int i;
    int plus=1;
    int t=n;
    
    struct pnumber p;
    initall(&p);
    
    if(is_prime(n,&p))
    {
        printf("1*%d=%d\n",n,n);
        return;
    }
    
    for(i=0;;i++)
    {
        if(0 == t%p.p[i])
        {
            plus *= p.p[i];
            t = t/p.p[i];
            printf("*%d",p.p[i]);
            i--;
        }
        if( plus == n)
        {  
            break;
        }
    }
    printf("=%d\n",n);
    return;
}

int main()
{
    solve_to_pri(151);
}
