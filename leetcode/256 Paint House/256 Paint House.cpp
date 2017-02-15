// 256 Paint House.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        if (costs.empty())return 0;
        int n = costs.size();
        int c = costs[0].size();

        vector<vector<int>> dp(n, vector<int>(c, 0));

        for (int i = 0; i < c; i++)
            dp[0][i] = costs[0][i];

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < c; j++)
            {
                int minc = numeric_limits<int>::max();
                for (int jj = 0; jj < c; jj++)
                {
                    if (jj == j) continue;
                    if (dp[i - 1][jj] < minc)
                        minc = dp[i - 1][jj];
                }
                dp[i][j] = minc + costs[i][j];
            }
        }

        return *min_element(dp[n - 1].begin(), dp[n - 1].end());


    }
};

int main()
{

    vector<vector<int>> costs;
    int c1[] = { 1,2,3 };
    int c2[] = { 2,1,3 };
    costs.push_back(vector<int>(c1, c1 + 3));
    costs.push_back(vector<int>(c2, c2 + 3));

    Solution s;
    auto cost = s.minCost(costs);
    return 0;
}

