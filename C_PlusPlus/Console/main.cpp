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
#include "reserve_resize.h"         //测试STL的reserve & resize 方法
#include "knapstack.h"              //0-1 背包问题
#include "CppProgram.h"             //《C++高质量编程》 里的代码
#include "BigNumMultiply.h"         //大数相乘的实现

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

void testHuaWeiMianshi()
{
    char* str1 = "abc";
    char* str2 = "abc";
    //char[] str3 = "abc";
    //char[] str4 = "abc";
    const char* str5 = "abc";
    const char* str6 = "abc";
    //const char[] str7 = "bac";
    //const char[] str8 = "bac";

    //cout << (str1 == str2) << endl; //是0 不是false
    //cout << (str5 == str6) << endl; //是0 不是false

    /*
    会初始化为数组, 关键是后面的几个0
    [1, 2,
     3, 0,
     0, 0]
    */
    int a[3][2] = { 1,2,3 };// 真的会初始化后面所有的空元素为 '0'，略神奇 

    for (int i = 0; i < 3; i++)
    {
        //cout << "cout<<a[i] = " << a[i] << endl;
        for (int j = 0; j < 2; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

}


//测试函数memccpy(遇到目标字符串则会停止复制)  似乎可以用于快速地识别一个字符是否在字符串中
//如果目标字符c 没有被复制，则返回NULL，否则，返回目标字符c 后面紧挨一个字符位置的指针。
int testMemccpy(void)
{
    char *src = "This is the source string !";
    char dest[80];
    char *ptr;
    ptr = (char *)memccpy(dest, src, 'i', strlen(src));
    //ptr = (char *)memccpy(dest, src, '!', strlen(src));
    if (ptr)
    {
        *ptr = '\0';
        printf("The character was found: %s\n", dest);
    }
    else
        printf("The character wasn't found\n");
    return 0;
}


int main(void)
{
    BigNumMultiplyMain();

    return 0;
}