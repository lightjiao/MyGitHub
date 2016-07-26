#include <stdio.h>
#include <stdlib.h>

char* mystrcopy(char *a, char *b)
{
    int i;
    for(i = 0;'\0' != *(b+i);i++)  /////////////////////////////////
    {
        *(a+i) = *(b+i);
    }

    *(a+i+1) = 0;

    return a;

}

char* mystrcopybetter(char *a, char *b)  //////////////////////////
{
    int i = -1;
    do
    {
        i++;
        a[i] = b[i];
    }while(0 != b[i]);

    return a;
}

char* recopystr(char *a,  char *b)
{
    int i, j;
    for(i = 0;'\0'! = b[i];i++)
    {
        ;
    }

    for(j = 0;'\0'! = *(b+j);j++)
    {
        *(a+i-j-1) = *(b+j);
    }
    *(b+i) = '\0';

    return a;
}

int strl(char *a)
{
    int i;
    for(i = 0;0! = *(a+i);i++)
    {
        ;
    }
    return i;
}

char* catstr(char *a, char *b)
{
    int i, j, k;
    k = strl(a);
    for(i = k, j = 0;0! = *(b+j);j++, i++)
    {
        *(a+i)  =  *(b+j);
    }
    *(a+i) = 0;
    return a;
}

char* findchar(char *a, char n)
{
    int i;
    for(i = 0;0!=a[i];i++)
    {
        if(a[i] == n)
        {
            return (a+i+1);
        }
    }
    return NULL;
}

void findcharplus(char *a, char n)
{
    int s;
    char *p;
    p = findchar(a, n);
    while(NULL != p)
    {
        s = p-a;
        printf("%5d", s);
        p = findchar(p+1, n);
    }
    printf("\n");
    return ;
}


int rejectchar(char *a, char *b)
{
    int i, j = 0, n, m;
    char *p;
    n = strl(a);
    m = strl(b);
    for(i = 0;i<n;i++)
    {
        p = findchar(b, a[i]);
        if(NULL == p)
        {
            a[j] = a[i];
            j++;
           
        }
    }
    a[j] = 0;
    return j;
}

int keepchar(char *a, char *b)
{
    int s = 0, i, n, m;
    char *p;
    n = strl(a);
    m = strl(b);
    for(i = 0;i<n;i++)
    {
        p = findchar(b, a[i]);
        if(NULL !=  p)
        {
            a[s] = a[i];
            s++;
        }
    }
    a[s] = 0;
    return s;
}

char* delrepeatchar(char *a)
{
    int i, j = 0, n;
    n = strl(a);
    char *p;
    for(i = 0;i<n;i++)
    {
        p = findchar(a, a[i]);
        if( (p-a) == i+1 )
        {
            a[j] = a[i];
            j++;
        }
    }
    a[j] = 0;
    return a;
}

char* delchar(char *a, char n)
{
    int i, j = 0, l;
    l = strl(a);
    for(i = 0;i<l;i++)
    {
        if(n != a[i])
        {
            a[j]  =  a[i];
            j++;
        }
    }
    a[j] = 0;
    return a;
}


char* mymemset(char *d, char c, int n)
{
    int i;
    for(i = 0;i<n;i++)
    {
        *(d+i) = c;
    }
    return d;
}

char* mymemcpy(char *d, char *s, int n)
{
    int i;
    for(i = 0;i<n;i++)
    {
        *(d+i) = *(s+i);
    }
    return d;
}

void getmem(char **str)
{
    *str = malloc(100);
    return;
}

int mystrcmp(char *d, char *s)
{
    int i;
    for(i = 0;'\0'! = *(d+i);i++)
    {
        if(*(d+i) > *(s+i))
        {
            return 1;
        }
        if(*(d+i) < *(s+i))
        {
            return -1;
        }
    } 
   
    if('\0'! = *(s+i))
    {
        return -1;
    }    
    
    return 0;
}

int maxsum(int *a, int n, int *b)
{
    int i = 0, j = 0;
    int begin  =  0;
    int end    =  0;
    int max    =  a[0];
    int sum    =  0;
    for(j = 0;j<n;j++)
    {
        sum += a[j];
        if(sum > max)
        {
            max = sum;
            begin  =  i;
            end    =  j;
        }
        if(sum < 0)
        {
            i = j+1;
            sum  =  0;
        }
    }
    b[0] = begin;
    b[1] = end;
    return max;
}

int maxcommon(int a, int b)
{
    int c;
    if(a < b)
    {
        c = a;
        a = b;
        b = c;
    }
    if((0 == b)||(0 == a))
    {
        printf("fault number!\n");
        return -1;
    }
    while(1)
    {
        c  =  a%b;
        if(0 == c)
        {
            return b;
        }
        else
        {
            a = b;
            b = c;
        }
    }
}

int remaxcommon(int a, int b)
{
    int c;
    if(a < b)
    {
        c = a;
        a = b;
        b = c;
    }
    if((0 == b)||(0 == a))
    {
        printf("fault number!\n");
        return -1;
    }
    if(0 == a%b)
    {
        return b;
    }
    else
    {
        c = a;
        a = b;
        b = c%b;
        remaxcommon(a, b);
    }
}

int mincommon(int a, int b)
{
    
    int c;
    c  =  maxcommon(a, b);
    return (a*b)/c;
}

int* changecash(int n)
{
    int i;
    int cash[]  = {100, 50, 20, 10, 5, 1};
    int *change = NULL;
    change = malloc(6*sizeof(int));
    if(NULL == change)
    {
        printf("malloc failed!\n");
        return ;
    }
    for(i = 0;i<6;i++)
    {
        change[i]  =  n/cash[i];
        n % =  cash[i];
    }
    return change;
}

int myatoi(char *a)
{
    int num  =  0;
    for(;0! = *a;a++)
    {
        num * =  10;
        num + =  *a - '0';
    }
    return num;
}

/*
int main(int argc, char **argv)
{
    char c[] = "123";
    int num;
    num  =  myatoi(c);
    printf("%d\n", num);

}
*/
