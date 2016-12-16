#ifndef _KNAPSTACK_H__
#define _KNAPSTACK_H__

/* 具体详细内容说明 */
/* http://www.hawstein.com/posts/dp-knapsack.html */

using namespace std;

#define KNAPSTACK_MANN 1000   //n 个宝石
#define KNAPSTACK_MAXC 100000 //C 的容量

int knapstack_V[KNAPSTACK_MANN]; //volume(宝石体积) 
int knapstack_W[KNAPSTACK_MANN]; //worth (宝石价值)
int knapstack_X[KNAPSTACK_MANN]; //exist (宝石是否装入)

int knapstack_d[KNAPSTACK_MANN][KNAPSTACK_MAXC]; // d(i, j) = MAX{ d(i - 1, j), d(i-1,j - V[i-1]) + W[i-1] } 的表达式

int test_knapstack()
{
    freopen("data.in", "r", stdin);   //重定向输入流
    //freopen("data.out", "w", stdout); //重定向输出流

    int n, C;

    while (scanf("%d %d", &n, &C) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            scanf("%d %d", &knapstack_V[i], &knapstack_W[i]);
            knapstack_X[i] = 0;//初始化是否装入袋子的参数
        }

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= C; j++)
            {
                knapstack_d[i][j] = i == 0 ? 0 : knapstack_d[i - 1][j];
                if (i > 0 && j >= knapstack_V[i-1])
                {
                    if (knapstack_d[i][j] < knapstack_d[i - 1][j - knapstack_V[i - 1]] + knapstack_W[i - 1])
                    {
                        knapstack_d[i][j] = knapstack_d[i - 1][j - knapstack_V[i - 1]] + knapstack_W[i - 1];
                        
                        //knapstack_X[i-1] = 1; //像这样的操作为什么不对呢？
                    }
                    else
                    {
                        //knapstack_X[i-1] = 0;
                    }
                }
            }
        }
        printf("最大价值：%d\n", knapstack_d[n][C]); //最终求解的最大值
        
        //正确的装袋策略
        int j = C;
        for (int i = n; i > 0; i--)
        {
            if (knapstack_d[i][j] > knapstack_d[i - 1][j])
            {
                knapstack_X[i - 1] = 1;
                j = j - knapstack_V[i - 1];
            }
        }

        printf("装袋策略：");
        for (int i = 0; i < n ;i++)
        {
            printf("%d ", knapstack_X[i]);
        }
        printf("\n\n");
    }
    
    fclose(stdin);

    return 0;
}

#endif // _KNAPSTACK_H__
