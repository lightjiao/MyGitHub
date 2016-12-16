
#ifndef __CPP_PROGRAM_H__
#define __CPP_PROGRAM_H__

#include <stdio.h>
#include <assert.h>
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
    //断言的判断还是很重要的
    assert((NULL != strSrc) && (NULL != strDest));
    
    char* address = strDest;
    while ((*address++ = *strSrc++) != '\0')
    {
        NULL;
    }

    /* 我自己写的复制方法 复制对了，但是return 的地址不对， 代码也不够简洁
    for (; *strSrc != '\0'; strSrc++)
    {
        *strDest = *strSrc;
        strDest++;
    }
    strDest++;
    *strDest = '\0';
    */

    return strDest; // 此处返回char* 类型 是为了实现链式表达， 例如 int length = strlen(strcpy(strDest, "hello world!"));
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
};

//构造函数的时候 一次性分配好所需的 内存地址空间，不需要 一步一步increase，我是不是傻啊
MyString::MyString(const char* str)
{
    //此处的NULL指针判断是否有必要，因为标准的 string方法 对NULL指针的构造会报错
    if (NULL == str)
    {
        m_sData = (char*)malloc(1);
        *m_sData = '\0';
    }
    else
    {
        m_nSize = mystrlen(str);
        m_nCapcity = m_nSize + 1;

        m_sData = (char*)malloc(m_nCapcity); // new char[m_nCapcity]
        mystrcpy(m_sData, str);
    }
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
    //*重要* 检查自赋值
    if (this == &mystringSrc)
    {
        return *this;
    }

    free(m_sData);
    m_nSize = mystringSrc.m_nSize;
    m_nCapcity = m_nSize + 1;

    m_sData = (char*)malloc(m_nCapcity);

    mystrcpy(m_sData, mystringSrc.m_sData);

    return *this;   // 为什么不是 “return this”？？ 返回的是本对象的引用
}


#endif
