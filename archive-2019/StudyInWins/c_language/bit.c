#include <stdio.h>

//int main(int argc,char *argv[])
//int main(int argc,char **argv)
#define SETBIT(a,n )
#define CLEAR(a,n) ((a)&(~(1<<(n-1))))
#define SETBIT(a,n) ((a)&(~(1<<((n)-1))))
#define RESERVE(a,n) ((a)^(1<<((n)-1)))
#define REVERSE2(a,n,m) ((a)^((1<<((n)-1)|(1<<((m)-1)))))
#define MOVE(a,n,m) (((((a)>>((n)-1))&1)<<((m)-1))|((a)&(~(1<<((m)-1)))))
#define EXCHANGE(a,n,m) ((((((a)>>((m)-1))&1)<<((n)-1))|((((a)>>((n)-1))&1)<<((m)-1)))|((CLEAR(a,n))|(CLEAR(a,m))))

#define SETBIT(a,n)       ((a)|(1<<((n)-1)))
#define SETBIT2(a,n,m)    ((a)|((SETBIT(1,(n)))|(SETBIT(1,(m)))))
#define SETBIT3(a,n)      ((a)|(~(1<<((n)-1))))
#define CLEARBIT(a,n)     ((a)&(~(1<<((n)-1))))
#define CLEARBIT2(a,n,m)  ((a)&(~((SETBIT(1,(n)))|(SETBIT(1,(m))))))
#define REVERSEBIT(a,n)   

int main()
{
    int a;
    a = EXCHANGE(0x8,2,4);
    printf("hello 0x%x\n",a);
    return 0;
}


