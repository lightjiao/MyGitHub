#include <iostream>
#include <algorithm>
#include "limits.h"
#include <vector>
#include <map>

using namespace std;

/**
 * 最长上升子序列（LIS）问题：给定长度为n的序列a，从a中抽取出一个子序列，这个子序列需要单调递增。问最长的上升子序列（LIS）的长度。
 * e.g. 1,5,3,4,6,9,7,8的LIS为1,3,4,6,7,8，长度为6。
 */
void lonestIncrSubStr(vector<int> numbers)
{
    cout << endl;
    for (auto &&n : numbers)
    {
        cout << n << " ";
    }
    cout << endl;

    // 一个substring 可能有多个LIS
    vector<int> dp(numbers.size(), 1);

    int ans = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (numbers[j] < numbers[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        cout << "dp[" << i + 1 << "] = " << dp[i] << endl;

        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
}

int main()
{
    lonestIncrSubStr({6, 7, 8, 9, 0});
    lonestIncrSubStr({6, 7, 8, 9, 0, 1, 2, 3, 4, 5});
    lonestIncrSubStr({1, 5, 3, 4, 6, 9, 7, 8});
}

/**
 * 关于DP的一个思考结果
 * 划分DP的子问题答案的时候，子问题的内容是要包含所在节点的信息的，不然会造成拼接子答案的时候丢失掉子信息
 * 举例：
 * LIS问题，我一开始想的是，dp[] 数组的i 下表存储的信息是从 0-i 这么多数据中的LIS信息
 * 但这样是不对的，是有可能会丢失 [i] 下标自身的信息的 (测试用例 678012345)
 * 而有效的划分应该是 dp[] 数组的 i 下标存储的信息是 以 i 为结尾的子串的LIS，这里有个前提条件是以 i 为结尾
 * 所以最终取结果的时候，只需要将 dp[] 遍历一遍找出最大数即可
 */