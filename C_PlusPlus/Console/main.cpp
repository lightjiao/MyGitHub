#include <iostream>
#include "stdio.h"
#include "stdint.h"
#include "vector"
#include "time.h"
#include "get100.h"
#include <cmath>
#include "string.h"
#include "stdlib.h"
#include "StringWithMySplitFunc.h"
#include "charReader.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4305) // (33)  “初始化”: 从“int”到“char”截断
#pragma warning(disable: 4309) // (33)  “初始化”: 截断常量值
#pragma warning(disable: 4018) // (240) “<”: 有符号/无符号不匹配 
#pragma warning(disable: 4477) // (67)  “printf”: 格式字符串“%x”需要类型“unsigned int”的参数，但可变参数 2 拥有了类型“int *”


using namespace std;

void func_1()
{
    // 小字节序：0  44  大字节序：1023  44
    int a[10];
    int  i = 0;
    
    for (i; i < 10; i++)
    {
        *(a + i) = i + 1014;
    }
    
    short *p = (short*)(&a + 1);//此处会跳过整个数组a  //a+1是内存地址以[数组元素的长度]加一， &a+1是内存地址[以整个数组的长度]加一
    short *q = p - 1;
    char c = 300;
    char* d = &c - 1;
    printf("%d %d\n", *q, c);   //大字节序：24,_      小字节序：10,_(0, 44)
    return;
}


void func_2()
{
    int a[3][3]    = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    int (*x)[3]    = a;
    int *k         = a[0];
    int (*y)[3][3] = &a;
    int (*q)[3]    = &a[0];
    int *z         = &a[0][0];
    printf("%d\n", (*(x + 1))[0]);    // 4
    printf("%d\n", *(k + 1));         // 2
    printf("%d\n", (*(*(y + 1)))[0]); // _____?
    printf("%d\n", (*(q + 1))[0]);    // 4
    printf("%d\n", *(z + 1));         // 2
    int *p = (int *)(y + 1);
    printf("%d\n", *(p - 1));         // 9
    return;                           // good, answer is right!
}

void test_func_1()
{
    short a[5] = { 0, 1, 2, 3, 4 };
    int   b[5] = { 0, 1, 2, 3, 4 };
    int* p = (int*)a;
    p++;
    printf("&a=%x\n&p=%x\n", &a, p);
    printf("a[0] = %d\n", a[0]);
    printf("  *p = %d\n", *p);
    printf("sizeof(a) = %d\n", sizeof(a));
    printf("sizeof(short)=%d\nsizeof(int)=%d\n", sizeof(short), sizeof(int));
    return;
}

void TrueSwamp(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
    return;
}

typedef uint32_t uint_32_t;

//通过位移，快速的计算开根号操作，但结果不够精确
float fast_sqrt(float x)
{
    uint_32_t x_bits = 0;
    x_bits = *((uint_32_t*) &x);
    x_bits = (x_bits >> 1) + 532369198;
    return *((float*)&x_bits);
}


//此splite函数无法区分一种特殊情况, 字符串为 "弢|你好啊|123|弢弢弢|abc" 按照 "|" 为分隔符时 会出错，原因是 汉字 "弢" 与分隔符 "|" 有相同的ACSII码
//C++的string 类 find以及C 语言本身的 strtok方法都无法区分这种特殊情况
int strsplit(const char *str, char *parts[], const char *delimiter)
{
    char *pch;
    int i = 0;
    char *copy = NULL, *tmp = NULL;
    copy = strdup(str);
    
    if (!copy)
    {
        goto bad;
    }
    
    pch = strtok(copy, delimiter);
    tmp = strdup(pch);
    
    if (!tmp)
    {
        goto bad;
    }
    
    parts[i++] = tmp;
    
    while (pch)
    {
        pch = strtok(NULL, delimiter);
        
        if (NULL == pch) { break; }
        
        tmp = strdup(pch);
        
        if (!tmp)
        { goto bad; }
        
        parts[i++] = tmp;
    }
    
    free(copy);
    return i;
bad:
    free(copy);
    
    for (int j = 0; j < i; j++)
    {
        free(parts[j]);
    }
    
    return -1;
}
//测试splite函数， 能够按照汉字为分隔符进行分割，但区分不了汉字 "弢" 与分隔符 "|"
void test004()
{
    char str[] = "123弢啦啦弢abc弢";//"弢|你好啊|123|弢弢弢|abc"
    char *parts[8];
    size_t size = strsplit(str, parts, "弢"); //"|"
    int i = 0;
    
    for (; i < size; ++i)
    {
        printf("%s\n", parts[i]);
    }
    
    return;
}

//西山居面试题，递归+循环
int cc(int i)
{
    for (;  i < 4; )
    {
        std::cout << cc(++i);
    }
    return i;
}
void testcc()
{
    cc(1);
    return;
}


void main(void)
{
	StringWithMySplit("中a|弢一你好一啊一|123|一弢弢弢|一abc").MysplitString('|');
	//StringWithMySplit().MysplitString('|');

// 	StringWithMySplit a = StringWithMySplit("a|弢一你好一啊一|123|一弢弢弢|一abc");
// 
// 	//cout << a.m_str << endl;
// 
//     char* pSrc = "a|弢一你好一啊一|123|一弢弢弢|一abc";
// 
// 	char* pDest = new char[strlen(pSrc)];
// 
// 	a.g2u(pSrc, strlen(pSrc), pDest, strlen(pSrc));
// 
// 	cout << pDest << endl;

	
    return;
}