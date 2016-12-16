#include <iostream>
#include <string>
#include <stdlib.h>
#include "calculator.h"

calcu::calcu(unsigned int space):numstack(space),opstack(space)
{

}

void calcu::clear(void)
{
    numstack.clear();
    opstack.clear();
}

int calcu::oplevel(char op)
{
    if((op == '+')||(op == '-'))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

double calcu::opcompute(double a,double b,char op)
{
    if(op == '+')
    {
        return a+b;
    }
    else if(op == '-')
    {
        return a-b;
    }
    else if(op == '*')
    {
        return a*b;
    }
    else if(op == '/')
    {
        if(b == 0)
        {
            throw string("div num is zero!");
        }
        return a/b;
    }
}

double calcu::compute(const char *s)
{
    const char *pstr = s;
    char *psave = NULL;
    double num;
    char op;
    double a,b;
    char opinstack;

    while(0 != *pstr)
    {
        if((*pstr >= '0')&&(*pstr <= '9'))
        {
            num = strtod(pstr,&psave);
            pstr = psave;
            numstack.push(num);
        }
        else
        {
            if(opstack.isempty())
            {
                opstack.push(*pstr);
                pstr++;
            }
            else
            {
                op = *pstr;
                opinstack = opstack.peek();
                if(oplevel(op) > oplevel(opinstack))
                {
                    opstack.push(op);
                    pstr++;
                }
                else
                {
                    b  = numstack.pop();
                    a  = numstack.pop();
                    op = opstack.pop();
                    a  = opcompute(a,b,op);
                    numstack.push(a);
                }
            }
        }
    }
    while(!opstack.isempty())
    {
        if(numstack.isempty())
        {
            throw string("operator chr without num!");
        }
        b  = numstack.pop();
        a  = numstack.pop();
        op = opstack.pop();
        a = opcompute(a,b,op);
        numstack.push(a);
    }
    if(numstack.count() > 1)
    {
        throw string("two or more num without operator chr");
    }
    num = numstack.pop();
    return num;
}

double calcu::compute(string &s)
{
    return compute(s.c_str());
}

int main(int argc,char *argv[])
{
    try
    {
        calcu calcu1;
        cout<<calcu1.compute(argv[1])<<endl;
    }
    catch (string s)
    {
        cout<<s<<endl;
    }
}
