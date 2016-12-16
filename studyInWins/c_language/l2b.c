#include <stdio.h>

int l2b(int n)
{
    char *p,temp;
    p=(char*)&n;
    temp=*p;
    *p=*(p+3);
    *(p+3)=temp;

    temp=*(p+1);
    *(p+1)=*(p+2);
    *(p+2)=temp;

    return n; 
}

int l2b2(int n)   
{
    short temp;
    short *p=(short*)&n;
    temp=*p;
    *p=*(p+1);
    *(p+1)=temp;
    return n;
}

int main()
{
    int a=0x12345678,b,c;
    b=l2b(a);           //output 78563412
    c=l2b2(a);          //output 56781234
    printf("%x \n%x \n",b,c);
    return 0;
}
