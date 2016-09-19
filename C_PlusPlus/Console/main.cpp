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
#include "reserve_resize.h"

#pragma warning(push)
#pragma warning(disable: 4996)
// #pragma warning(disable: 4305) // (33)  “初始化”: 从“int”到“char”截断
// #pragma warning(disable: 4309) // (33)  “初始化”: 截断常量值
// #pragma warning(disable: 4018) // (240) “<”: 有符号/无符号不匹配 
// #pragma warning(disable: 4477) // (67)  “printf”: 格式字符串“%x”需要类型“unsigned int”的参数，但可变参数 2 拥有了类型“int *”


using namespace std;


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

#include <errno.h>
void test_strtod()
{
    const char *p = "111.11 -2.22 0X1.BC70A3D70A3D7P+6  1.18973e+309";
    printf("Parsing '%s':\n", p);
    char *end;
    for (double f = strtod(p, &end); p != end; f = strtod(p, &end))
    {
        printf("'%.*s' -> ", (int)(end - p), p);
        p = end;
        if (errno == ERANGE) {
            printf("range error, got ");
            errno = 0;
        }
        printf("%f\n", f);
    }
}

void main(void)
{
	//测试STL的reserve、resize方法
	//test_Reserve_Resize_Main();

    test_strtod();

    return;
}