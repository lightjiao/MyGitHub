#include <stdio.h>

struct array
{
    int *p;
    int n;
    void (*show)(int *,int n);
};

void swap(int a,int b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
    return;
}

void realswap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
    return;
}

void showarray(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d   ",a[i]);
    }
    printf("\n");
    return;
}

int sumarray(int a[],int n)
{
    int i,sum;
    sum=0;
    for(i=0;i<n;i++)
    {
        sum=sum+a[i];
    }
    return sum;
}

void copyarray(int a[],int *b,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        b[i]=a[i];
    }
    return;
}

void recopyarray(int *a,int *b,int n)
{
    int i;
    int j;
    
    for(i=0;i<n;i++)
    {
        b[n-i-1]=a[i];
    }
    
    return;
}

void exchangearray(int *a,int *b,int n)
{
    int temp,i,j;
    for(i=0;i<n;i++)
    {
        temp=a[i];
        a[i]=b[i];
        b[i]=temp;
    }
    return;
}

/*
int main()
{   
    int a=10,b=20;
    printf("a=%d\nb=%d\n",a,b);
    swap(a,b);
    printf("\n\nswap\na=%d\nb=%d\n",a,b);
    realswap(&a,&b);
    printf("\n\nrealswap\na=%d\nb=%d\n",a,b);

}
*/
