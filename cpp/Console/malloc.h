#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
 * 示例一
 * 程序崩溃，Example_1_GetMemory函数并不能传递动态内存，Example_1_Test函数中的str一直是NULL
 */
void Example_1_GetMemory(char* p)
{
    p = (char*)malloc(100);
}

void Example_1_Test(void)
{
    char* str = NULL;
    Example_1_GetMemory(str);
    strcpy(str, "Hello world!");
    printf("%s\n", str);
}


/*
 * 示例二
 * 可能是乱码，Example_2_Getmemory返回的是指向“栈内存”的指针，该指针的地址不是 NULL，但其原现的内容已经被清除，新内容不可知
 * 解决办法：使用malloc来分配内存； 将变量设置为static类型
 */
char* Example_2_Getmemory(void)
{
    char p[] = "Hello world!";

    return p;
}

void Example_2_Test(void)
{
    char* str = NULL;
    str = Example_2_Getmemory();
    printf("%s\n", str);
}


/*
 * 示例三
 * 正常运行，但内存泄漏
 */
void Example_3_Getmemory(char**p, int num)
{
    *p = (char*)malloc(num);
}

void Example_3_Test(void)
{
    char* str = NULL;
    Example_3_Getmemory(&str, 100);
    strcpy(str, "Hello world!");
    printf(str);
}


/*
 * 示例四
 * 篡改动态内存区的内容，后果难以预料，非常危险。因为free(str);之后，str成为野指针，if(str != NULL)语句不起作用。
 * 野指针成因：初始化、释放过后没有及时的指向NULL并且再次被引用； 超出作用域的调用（一对大括号为一个作用域）；基于栈分配的局部变量地址，如Example_2_Getmemory
 * 野指针 Wikipedia https://zh.wikipedia.org/wiki/%E8%BF%B7%E9%80%94%E6%8C%87%E9%92%88
 */

void Example_4_Getmemory(char**p, int num)
{
    *p = (char*)malloc(num);
    strcpy(*p, "Hello");
    free(*p);
}
void Example_4_Test(void)
{
    char* str = (char*)malloc(100);
    strcpy(str, "Hello");
    free(str);

    if (NULL != str)
    {
        strcpy(str, "world!");
        printf(str);
    }
}


#endif