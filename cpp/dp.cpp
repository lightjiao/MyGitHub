#include <iostream>
#include <algorithm>
#include "limits.h"
#include <vector>
#include <map>

using namespace std;

/**
 * 面值为 1、5、11 的钞票，用DP算出，凑出 15 的时候，最少花费多少张钞票
 */
void dp_money(int money)
{
    vector<vector<int>> dp; // = new vector<vector<int>>(money + 1);

    dp.push_back(vector<int>{});
    for (int i = 1; i <= money; i++)
    {
        vector<int> cost = {};
        if (i - 1 >= 0)
        {
            vector<int> newCost(dp[i - 1]);
            newCost.push_back(1);

            if (cost.size() == 0 || newCost.size() < cost.size())
            {
                cost = newCost;
            }
        }
        if (i - 5 >= 0)
        {
            vector<int> newCost(dp[i - 5]);
            newCost.push_back(5);

            if (cost.size() == 0 || newCost.size() < cost.size())
            {
                cost = newCost;
            }
        }
        if (i - 11 >= 0)
        {
            vector<int> newCost(dp[i - 11]);
            newCost.push_back(11);

            if (cost.size() == 0 || newCost.size() < cost.size())
            {
                cost = newCost;
            }
        }

        dp.push_back(cost);
    }

    for (int i = 0; i < dp.size(); i++)
    {
        cout << i << " = ";
        for (int j = 0; j < dp[i].size(); j++)
        {
            if (j != 0)
            {
                cout << " + ";
            }

            cout << dp[i][j];
        }

        cout << endl;
    }

    return;
}

int main()
{
    dp_money(16);

    return 0;
}