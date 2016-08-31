#include <iostream>
#include "stdio.h"
#include "stdint.h"
//#include "winsock.h"//htons ntohs
//#include "winsock2.h"//htons ntohs
#include "vector"
#include "time.h"
#include "get100.h"
#include <cmath>

using namespace std;

void func_1()
{   // 小字节序：0  44  大字节序：1023  44
    int a[10];
    int  i = 0;
    for (i; i < 10; i++)
    {
        *(a + i) = i+1014;
    }
    short *p = (short*)(&a + 1);//此处会跳过整个数组a  //a+1是内存地址以[数组元素的长度]加一， &a+1是内存地址[以整个数组的长度]加一
    short *q = p - 1;

    char c = 300;
    char* d = &c - 1;
    printf("%d %d\n", *q, c);           //大字节序：24,_      小字节序：10,_(0, 44)

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

    return;                           //good, answer is right!
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
    printf("sizeof(a) = %d\n",sizeof(a));
    printf("sizeof(short)=%d\nsizeof(int)=%d\n", sizeof(short), sizeof(int));

    return;
}

class testPrint
{
public:
    testPrint(unsigned int n)
    {
        printf("%d:construct!\n",n);
    };

    ~testPrint()
    {
        printf("release!\n");
    };

    void testPrint::ThePrintFunc(unsigned int n)
    {
        printf("%d\n", n);
    }
};

void TrueSwamp(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;

    return;
}



void PrintMultiTable()
{
    int i, j = 0;
    for (i = 1; i <= 9;i++)
    {
        for (j = 1; j <= i;j++)
        {
            printf("%d * %d = %d   ", j, i, i*j);
            if (i*j<10)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

typedef uint32_t uint_32_t;

//what is this
float fast_sqrt(float x)
{
    uint_32_t x_bits = 0;
    
    x_bits = *((uint_32_t*) &x);
    
    x_bits = (x_bits >> 1) + 532369198;

    return *((float*)&x_bits);
}

//测试vector的 erase方法
void vector_test()
{
    vector<int> vecInt;
    for (int i = 0; i < 10; i++)
    {
        vecInt.push_back(i);
    }

    printf("\n\n***********************\n");
    vector<int>::iterator it = vecInt.begin();
    for (; it != vecInt.end();)
    {
        printf("%d\n", *it);
        it++;
    }

    printf("\n\n***********************\n");
    it = vecInt.begin();
    for (; it != vecInt.end();)
    {
        printf("%d\n", *it);
        it = vecInt.erase(it);
    }
    printf("hello");
    for (; it != vecInt.end();)
    {
        printf("%d\n", *it);
        it = vecInt.erase(it++);
    }

    vecInt.clear();
    for (int i = 0; i < 10; i++)
    {
        vecInt.push_back(i);
    }

    printf("\n\n***********************\n");
    it = vecInt.begin();
    for (; it != vecInt.end();)
    {
        printf("%d\n", *it);
        it = vecInt.erase(it++);
    }
    printf("hello");
    for (; it != vecInt.end();)
    {
        printf("%d\n", *it);
        it = vecInt.erase(it++);
    }

    return;
}

void strangePow_2()
{
    double an = 0, sn = 0;//an为通项，sn为和
    int a, n;
    cout << "Please enter a,n:" << endl;
    cin >> a >> n;
    cout << pow(10, 2); //此处的输出结果没有换行导致显示结果出现1000 而不是100
    for (int i = 0; i < n; i++) {
        cout << an << endl;
        an += a*pow(10, i);
        sn += an;
    }
    cout << an << '\t' << sn << endl;
    cin >> a;
    return ;
}

void main()
{
    //get100();
    strangePow_2();
    
    return;
}