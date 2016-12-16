#include <stdio.h>

void setarray2(int *a,int n,int m)

{
    int i,j,s;
    printf("Please input a start number:");
    scanf("%d",&s);
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
           //*(*(a + i)+j) = s++;
           *(a+i*m+j) = s++;
        }
    }
    return;
}

void showarray2(int *a,int n,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%5d",*(a+i*m+j));            
        }
        printf("\n");
    }
    return;
}

int arrayplus(int *a,int *b,int *c,int n)
{
    int i;
    for(i=0;i<n;i++)
    {    
        *(c+i)=*(a+i)+*(b+i);            
    }
    return 0;
}

int arraysub(int *a,int *b,int *c,int n)
{   
    int i;
    for(i=0;i<n;i++)
    {
        *(c+i)=*(a+i)-*(b+i);
    }
    return 0;
}

int arraymul(int *a,int *b,int *c,int n,int m,int l)
{  
    int i,j,k,sum=0;

    for(i=0;i<n;i++)
    {
        for(k=0;k<l;k++)
        {
            for(j=0;j<m;j++)
            {
                sum= sum + ( (*(a+i*m+j)) * (*(b+j*l+k)) ) ;
            }
            *(c+i*l+k)=sum;
            sum=0;
        }
    }

    return 0;
}


/*
int main()
{
    int a[2][3],b[3][2],c[2][2];
    setarray2(&a[0][0],2,3);
    showarray2(&a[0][0],2,3);
    setarray2(&b[0][0],3,2);
    showarray2(&b[0][0],3,2);
    arraymul(&a[0][0],&b[0][0],&c[0][0],2,3,2);
    printf("The mul array is:\n");
    showarray2(&c[0][0],2,2);
    return 0;
}
*/
