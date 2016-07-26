#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <iostream>
#include <string.h>
#include <string>

using namespace std;

template <typename T>
class mystack
{
    public:
        mystack(unsigned int space=10);
        ~mystack();
        void push(T a);
        T    pop(void);
        bool isempty(void);
        T    peek(void);
        void clear(void);
        int  count(void);
    private:
        T *data;
        unsigned int space;
        unsigned int num;
        void increase(void);
};

template <typename T>
mystack<T>::mystack(unsigned int space)
{
    data = (T*)new T[space];
    num = 0;
    this->space = space;
}

template <typename T>
mystack<T>::~mystack()
{
    delete []data;
}

template <typename T>
int mystack<T>::count(void)
{
    return num;
}

template <typename T>
bool mystack<T>::isempty(void)
{
    return 0 == num;
}

template <typename T>
void mystack<T>::increase(void)
{
    T *newdata = new T[space*2];
    for(int i=0;i<num;i++)
    {
        newdata[i] = data[i];
    }
    space = space*2;
    delete []data;
    data = newdata;
}

template <typename T>
void mystack<T>::push(T a)
{
    if(space == num)
    {
        increase();
    }
    data[num] = a;
    num++;
}

template <typename T>
T mystack<T>::pop(void)
{
    if(isempty())
    {
        T tmp;
        return tmp;
    }
    num--;
    return data[num];
}

template <typename T>
T mystack<T>::peek(void)
{
    if(isempty())
    {
        T tmp;
        return tmp;
    }
    return data[num-1];
}

template <typename T>
void mystack<T>::clear(void)
{
    num = 0;
}

#endif
