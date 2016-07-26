#include <stdio.h>

int age(int n)
{
    int c;
    if(n==1)
        c = 10;
    else 
        c = age( n-1 ) + 2;
    return c;
}

int factorial(int n)
{
    int fac;
    if(0==n||1==n)
        fac = 1;
    else 
        fac = factorial(n-1)*n;
    return fac;
}

void move(char x,char y)
{
    printf("%c-->%c\n",x,y);
    return;
}

void hanoi(int n,char one,char two,char three)
{
    if(1==n)
        move(one,three);
    else
    {
        hanoi(n-1,one,three,two);
        move(one,three);
        hanoi(n-1,two,one,three);
    }
}

void myhanoi(int n,char a,char b,char c)
{
    if(1 == n)
    {
        printf("%c--->%c\n",a,c);
    }
    else
    {
        myhanoi(n-1,a,c,b);
        printf("%c--->%c\n",a,c);
        myhanoi(n-1,b,a,c);
    }
}

void Hanoi()
{
    int m;
    printf("input the number of disks:");
    scanf("%d",&m);
    printf("the step to move %d disks:\n",m);
    hanoi(m,'A','B','C');
    
    printf("my  step to move %d disks:\n",m);
    myhanoi(m,'a','b','c');
    return ;
}



/*
int main()
{
    Hanoi();
}
*/
