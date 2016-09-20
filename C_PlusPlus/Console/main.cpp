#include <iostream>
#include "stdio.h"
#include "stdint.h"
#include "vector"
#include "time.h"
#include <cmath>
#include "string.h"
#include "stdlib.h"

#include "get100.h"                 //网传1, 2, ..., 9数字组合结果等于 100
#include "StringWithMySplitFunc.h"  //split函数处理生僻汉字
#include "charReader.h"             //没能实现的json解析器
#include "reserve_resize.h"         //测试STL的reserve & resize 方法
#include "knapstack.h"              //0-1 背包问题

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


//lept_json 教程中 strtod的说明与验证
/* http://en.cppreference.com/w/c/string/byte/strtof */
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


int main(void)
{
    test_knapstack();
    return 0;
}