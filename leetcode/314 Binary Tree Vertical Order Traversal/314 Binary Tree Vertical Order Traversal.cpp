// 314 Binary Tree Vertical Order Traversal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utils\LeetCodeUtils.h"
 
class Solution {
public:
	vector<vector<int>> verticalOrder(TreeNode* root) {
		if (!root) return{};
		vector<vector<int>> left, right;
		vector<int> mid;

		queue<pair<TreeNode*, int>> q;
		q.push({ root, 0 });

		while (!q.empty())
		{
			auto cur = q.front().first;
			auto index = q.front().second;
			q.pop();
			if (cur->left) q.push({ cur->left, index - 1 });
			if (cur->right) q.push({ cur->right, index + 1 });

			if (index == 0)
				mid.push_back(cur->val);
			else if (index < 0)
			{
				if (-index > left.size())
					left.push_back({ cur->val });
				else
					left[-1 - index].push_back(cur->val);
			}
			else
			{
				if (index > right.size())
					right.push_back({ cur->val });
				else
					right[index - 1].push_back(cur->val);
			}
		}

		reverse(left.begin(), left.end());
		left.emplace_back(move(mid));
		for (auto& r : right)
			left.emplace_back(move(r));
		return left;
	}
};

int main()
{
	auto root = BuildTree("3,9,8,4,0,1,7,null,null,null,2,5,null,null,null,null,3");


	Solution s;
	auto ret = s.verticalOrder(root);
    return 0;
}

