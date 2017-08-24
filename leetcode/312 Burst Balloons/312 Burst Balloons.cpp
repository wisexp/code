// 312 Burst Balloons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	struct VW
	{
		VW(vector<int>& nums) :nums(nums) {}
		int operator[] (int i) const
		{
			if (i == 0 || i == nums.size() + 1) return 1;
			return nums.at(i - 1);
		}
		size_t size() const { return nums.size() + 2; }
		vector<int>& nums;
	};

	int maxCoins(vector<int>& nums) {
		VW wrapper(nums);
		int size = wrapper.size();
		vector<vector<int>> dp(size, vector<int>(size, 0));

		// dp[i][j] => j >= i+2, burst [i+1..j-1], keep [i] and [j];

		for (int dis = 2; dis < size; dis++)
		{
			for (int i = 0; i < size - dis; i++)
			{
				if (dis == 2)
					dp[i][i + dis] = wrapper[i] * wrapper[i + 1] * wrapper[i + 2];
				else
				{
					for (int k = 0; k <= dis - 2; k++)
					{
						int m1 = dp[i][i + k + 1];
						int m2 = wrapper[i] * wrapper[i + k + 1] * wrapper[i + dis];
						int m3 = dp[i + k + 1][i + dis];
						dp[i][i + dis] = max(dp[i][i + dis], m1 + m2 + m3);
					}
				}
			}
		}

		return dp[0][size - 1];
	}
};
int main()
{

	vector<int> nums = { 3,4 };
	Solution s;
	auto ret = s.maxCoins(nums);
    return 0;
}

