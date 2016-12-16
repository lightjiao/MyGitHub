#include <stdio.h>

void swap(int *a,int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return ;
}

int partition(int *a,int p,int r)
{
    int x = a[r];
    int i = p-1;
    int j;
    int tmp;
    for(j=p;j<r;j++)
    {
        if(a[j] < x)
        {
            i++;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    tmp = a[i+1] ;
    a[i+1] = a[r];
    a[r] = tmp;
    return i+1;
}

int partitionpre(int *a,int p,int r)
{
    int pos = a[p];
    int i = r+1;
    int j;
    int tmp;
    
    for(j=r;j>p;j--)
    {
        if(a[j] >= pos)
        {
            i--;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    tmp = a[i-1];
    a[i-1] = a[p];
    a[p] = tmp;
    return i-1;
}

int quicksort(int *a,int p,int r)
{
    int q;
    if(p < r)
    {
        q = partitionpre(a,p,r);
        quicksort(a,p,q-1);
        quicksort(a,q+1,r);
    }
    return ;
}

int bubblesort(int a[],int n)
{
    int i,j;
    int flag = 0;
    int tmp;
    for(i=0;i<n;i++)
    {
        flag = 0;
        for(j=0;j<n-1-i;j++)
        {
            if(a[j] > a[j+1])
            {
                swap(&a[j],&a[j+1]);
                flag = 1;
            }
        }
        if(0 == flag)
        {
            break;
        }
    }
}

int insertsort(int a[],int n)
{
    int i,j,k;
    int tmp;
    for(i=1;i<n;i++)
    {
        tmp = a[i];
        for(j=0;j<i;j++)
        {
            if(a[i] <= a[j])
            {
                break;
            }
        }
        for(k=i;k>=j;k--)
        {
            a[k] = a[k-1];
        }
        a[j] = tmp;
    }
}

int main()
{
    int i;
    int a[10] = {4,2,3,6,7,1,9,8,0,5};
    insertsort(a,10);

    for(i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}
