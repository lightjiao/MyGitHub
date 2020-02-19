#include <stdio.h>
#include "stack.h"

int myatoi(char *a)
{
    int num = 0;
    for(;0!=*a;a++)
    {
        num *= 10;
        num += *a - '0';
    }
    return num;
}

char* myitoa(int a)
{
    
}

int signjudge(char *a,char *b)
{
    if(('+' == a) || ('-' == a))
    {
        return 1;
    }
    else
    {
        if(('*' == b) || ('/' == b))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int main()
{
    struct mystack numstack;
    struct mystack signstack;
    char formula[1024];
    int a,b;
    char sign;
    int i;

    printf("please input a formula to cacula:\n");
    scanf("%c",&formula);
    len = strlen(formula);

    for(i=0;0 != formula[i] ;i++)
    {
        if(' ' == formula[i])
        {
            continue ;
        }
        if(0 != signstack->top)
        {
            if(signjudge(signstack->top,formula[i]))
            {
                b = myatoi(pop(&numstack));
                a = myatoi(pop(&numstack));
                sign = pop(&signstack);
                if('+' == sign)
                {
                    a = a+b;
                }
                if('-' == sign)
                {
                    a = a-b;
                }
                if('*' == sign)
                {
                    a = a*b;
                }
                if('/' == sign)
                {
                    a = a/b;
                }
                push(&numstack,myitoa(a));
            }
        }
        if((formula[i]<='9')&&(formula[i])>='0')
        {
            push(&numstack,formula[i]);
        }
        else
        {
            push(&signstack,formula[i]);
        }
    }
}
