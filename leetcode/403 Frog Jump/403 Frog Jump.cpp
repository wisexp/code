// 403 Frog Jump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
public:
	bool canCross(vector<int>& stones) {
		int size = stones.size();
		if (size == 0) return false;
		unordered_map<int, set<int>> dp;
		set<int> empty;
		for (auto i : stones)
			dp[i] = empty;
		dp[1].insert(1);
		int last = stones.back();
		for (int i = 1; i < size; i++)
		{
			for (auto s : dp[stones[i]])
			{
				for (int k = -1; k <= 1; k++)
				{
					int step = s + k;
					if (step <= 0) continue;
					int next = stones[i] + step;
					if (next > last) break;
					else if (next == last) return true;

					if (dp.find(next) == dp.end()) continue;
					dp[next].insert(step);
				}
			}
		}

		return !dp[last].empty();
	}
};
int main()
{

	vector<int> stones = {
		0,1,3,5,6,8,12,17 };

	Solution s;
	bool ret  = s.canCross(stones);
    return 0;
}

