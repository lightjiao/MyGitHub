
#ifndef __CPP_PROGRAM_H__
#define __CPP_PROGRAM_H__

#include <stdio.h>  
#include <tchar.h>  
#include <iostream>  
#include <vector>  
#include <string>  

using namespace std;

unsigned int mystrlen(const char* s)
{
    unsigned int len = 0;
    for (; *s != '\0'; s++)
    {
        len++;
    }
    return len;
}

//《C++高质量编程指南》中的strcpy
char* mystrcpy(char* strDest, const char* strSrc)
{
    for (; *strSrc != '\0'; strSrc++)
    {
        *strDest = *strSrc;
        strDest++;
    }
    strDest++;
    *strDest = '\0';

    return strDest;
}

void testMyStrcpy()
{
    char* p = "hello world!";
    char* p2 = (char*)malloc(20);

    mystrcpy(p2, p);

    cout << p << endl << p2 << endl;
}



//编写类String的构造函数、析构函数 和 赋值函数
class MyString
{
public:
    MyString(const char* str = NULL); 
    MyString(const MyString& mystringSrc);
    ~MyString(void);

    MyString& operator=(const MyString& mystringSrc);

private:
    char* m_sData;
    unsigned int m_nCapcity;
    unsigned int m_nSize;

    void _increase(void);
    void _increase(unsigned int nSize);
};

//构造函数的时候 一次性分配好所需的 内存地址空间，不需要 一步一步increase，我是不是傻啊
MyString::MyString(const char* str)
{
    m_nSize = mystrlen(str);
    m_nCapcity = m_nSize + 1;

    m_sData = (char*)malloc(m_nCapcity); // new char[m_nCapcity]
    mystrcpy(m_sData, str);

}

MyString::MyString(const MyString& mystringSrc)
{
    m_nSize = mystringSrc.m_nSize;
    m_nCapcity = m_nSize + 1;

    m_sData = (char*)malloc(m_nCapcity);
    mystrcpy(m_sData, mystringSrc.m_sData); //这里有一个疑问，为何可以访问到 mystring 的私有成员 ，“共有”、“私有” 不是与实例相关，而是与对象相关 这样吗？

}

MyString::~MyString(void)
{
    m_nCapcity = 0;
    m_nSize = 0;
    free(m_sData);
    m_sData = NULL;
}

MyString& MyString::operator =(const MyString& mystringSrc)
{
    if (m_nCapcity < mystringSrc.m_nSize + 1)
    {
        _increase(mystringSrc.m_nSize + 1);
    }
    /*
    while (m_nCapcity < mystringSrc.m_nSize + 1)
    {
        _increase();
    }
    */

    mystrcpy(m_sData, mystringSrc.m_sData);

    m_nSize = mystringSrc.m_nSize;

    return *this;   // 为什么不是 “return this”？？
}

void MyString::_increase(void)
{
    char* p = (char*)malloc(m_nCapcity * 1.5); //此处的浮点运算不知道会不会有问题
    memcpy(p, m_sData, m_nSize);

    free(m_sData);
    m_sData = p;
    m_nCapcity *= 1.5; //此处的浮点运算不知道会不会有问题
}

void MyString::_increase(unsigned int nCapcity)
{
    char* p = (char*)malloc(nCapcity);
    memcpy(p, m_sData, m_nSize);

    free(m_sData);
    m_sData = p;
    m_nCapcity = nCapcity;
}

#endif
