#include "get100.h"

#define TOP             (6561)      // 3的8次方
#define INVALID_N       (-99999)    // 特殊值

char g_ops[3] = { ' ', '+', '-' }; // 运算符表
int  g_values[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 顺序不能改变的数字序列

/** 打印算式 */
void print(char *p, int r)
{
    int i;

    printf("%d", g_values[0]);
    for (i = 1; i < 9; ++i)
    {
        if (p[i - 1] != ' ')
            printf(" %c ", p[i - 1]);
        printf("%d", g_values[i]);
    }
    printf(" = %d\n", r);
}

/** 以[f, t]闭合关系获取g_values的片段，如[1,3]将返回123，[8,8]将返回8 */
int vstrip(int f, int t)
{
    int sum = 0;

    for (; f <= t; ++f)
        sum = sum * 10 + g_values[f];

    return sum;
}

int calc(char *p)
{
    int last; // last标记待获取片段的开始位置
    int res; // res记录算式的运算结果
    int i;
    char op; // pos记录待运算的算符

    last = -1;
    op = -1;
    for (i = 0; i < 8;)
    {
        // 寻找下一个有效算符
        while (i < 8 && p[i] == ' ')
            ++i;
        if (i >= 8)
            break;

        if (-1 == last)
        {
            res = vstrip(0, i); 
        } 
        else
        {
            if ('+' == op)
                res += vstrip(last, i);
            else if ('-' == op)
                res -= vstrip(last, i);
            else
                return INVALID_N;
        }

        last = i + 1; // 更新片段的开始位置
        op = p[i]; // 更新待运算的算符

        ++i;
    }

    // 特殊处理8个算符全为空的情况
    if (-1 == last || -1 == op)
        return 123456789;

    // 最后一次运算
    if ('+' == op)
        res += vstrip(last, 8);
    else if ('-' == op)
        res -= vstrip(last, 8);
    else
        return INVALID_N;

    return res;
}

//this is the main()
int get100(void)
{
    int i, j;
    char vOps[8];

    for (i = 0; i < TOP; ++i)
    {
        int x = i;
        // 以3为基数，填充8个位置的算符
        for (j = 0; j < 8; ++j)
        {
            vOps[j] = g_ops[x % 3];
            x = x / 3;
        }
        
        if (100 == calc(vOps))
            print(vOps, 100);
    }

    return 0;
}