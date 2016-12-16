#ifndef __NIUKEWANG_FIRST_TEST_H__
#define __NIUKEWANG_FIRST_TEST_H__

#include <stdio.h>
#include <stdlib.h> //rand srand
#include <time.h>
#include <iostream>
#include <ostream>
#include <iterator>//ostream_iterator

using namespace std;

//从 0...n-1 中随机等概率的输出m 个不重复的数，这里我们假设 n 远大于 m
void knuth(int n, int m)
{
    srand((unsigned int)time(0)); //srand(time(NULL))
    for (int i = 0; i < n; i++)
    {
        if (rand() % (n - i) < m)
        {
            cout << i << endl;
            m--;
        }
    }

    return;
}


//分解质因数，入参为需要分解的数字和该数字的最小质因数(12， 2)
void prim(int m, int n)
{
    if (m >= n)
    {
        while (m % n) n++;
        m /= n;
        prim(m, n);
        cout << n << endl;
    }

    return;
}


//这种写法在全局变量枚举时候，x会被初始化为 0,在局部变量枚举时候是随机值
enum abc
{
    x1 = 3,
    x2, // = 4
    x3 = 1,
    x4, // = 2
    x5, // = 3
} x;


//关于 子类、父类 与虚函数、动态绑定相关的一些问题
class A
{
public:
    void FuncA()
    {
        printf("FuncA called\n");
    }
    virtual void FuncB()
    {
        printf("FuncB called\n");
    }
};
class B : public A
{
public:
    void FuncA()
    {
        A::FuncA();
        printf("FuncAB called\n");
    }
    virtual void FuncB()
    {
        printf("FuncBB called\n");
    }
};
int TestClassMain(void)
{
    B  b;
    A  *pa;
    pa = &b;
    A *pa2 = new A;
    pa->FuncA();    //pa=&b动态绑定但是FuncA不是虚函数，所以FuncA called
    pa->FuncB();    //FuncB是虚函数所以调用B中FuncB，FuncBB called  
    pa2->FuncA();   //pa2是A类指针，不涉及虚函数，调用的都是A中函数，所以FuncA called FuncB called
    pa2->FuncB();
    delete pa2;
    return 0;
}

//不明所以的两个函数  待续……
int FindSubString(char* pch)
{
    int   count = 0;
    char  * p1 = pch;
    while (*p1 != '\0')
    {
        if (*p1 == p1[1] - 1)
        {
            p1++;
            count++;
        }
        else {
            break;
        }
    }
    int count2 = count;
    while (*p1 != '\0')
    {
        if (*p1 == p1[1] + 1)
        {
            p1++;
            count2--;
        }
        else {
            break;
        }
    }
    if (count2 == 0)
        return(count);
    return(0);
}
void ModifyString(char* pText)
{
    char  * p1 = pText;
    char  * p2 = p1;
    while (*p1 != '\0')
    {
        int count = FindSubString(p1);
        if (count > 0)
        {
            *p2++ = *p1;
            sprintf(p2, "%i", count);
            while (*p2 != '\0')
            {
                p2++;
            }
            p1 += count + count + 1;
        }
        else {
            *p2++ = *p1++;
        }
    }
}
void TestModifyStringMain(void)
{
    char text[32] = "XYBCDCBABABA";
    ModifyString(text);
    printf(text);
}


//下面程序的功能是输出数组的全排列
//其中copy、swap 都是std 的函数， ostream_iterator<T>out(os, d),out是一个流迭代器，将类型为T的值写到输出流os中，并且每个值后面都输出一个d(premier p359)
void perm(int list[], int k, int m)
{
    if (k == m)
    {
        copy(list, list + m, ostream_iterator<int>(cout, " ")); // ostream_iterator #include<iterator>
        cout << endl;
        return;
    }
    for (int i = k; i < m; i++)
    {
        swap(list[k], list[i]);
        perm(list, k + 1, m);
        swap(list[k], list[i]);
    }
}
void TestPermMain()
{
    int a[] = { 1, 2, 3, 4 };
    perm(a, 0, 4);
}

int NiuKeWangTestMain()
{
    //TestModifyStringMain();
    TestPermMain();

    return 0;
}

#endif