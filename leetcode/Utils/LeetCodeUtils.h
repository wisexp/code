#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<string> Split(string input, char delimiter)
{
	vector<string> ret;
	int beg = 0;
	for (int cur = 0; cur < input.size(); cur++)
	{
		if (input[cur] == delimiter)
		{
			ret.push_back(input.substr(beg, cur - beg));
			beg = cur + 1;
		}
	}
	ret.push_back(input.substr(beg, input.size() - beg));
	return ret;
}

string PrintTree(TreeNode* root)
{
	if (!root) return "null";
	queue<TreeNode*> nodes;
	nodes.push(root);
	string ret;
	while (!nodes.empty())
	{
		auto cur = nodes.front();
		nodes.pop();
		if (cur)
			ret += to_string(cur->val);
		else
			ret += "null";

		ret += ",";
		if (cur)
		{
			nodes.push(cur->left);
			nodes.push(cur->right);
		}
	}
	ret.pop_back();
	return ret;
}

TreeNode* BuildTree(string input)
{
	queue<TreeNode*> nodesInLevel;
	TreeNode* root = nullptr;
	auto parts = Split(input, ',');
	bool forLeft = true;
	for (int i = 0; i < parts.size(); i++)
	{
		TreeNode* node = nullptr;
		if (parts[i] != "null")
		{
			int v = atoi(parts[i].c_str());
			if (root == nullptr)
			{
				root = new TreeNode(v);
				nodesInLevel.push(root);
				continue;
			}
			else
				node = new TreeNode(v);
		}
		else if (root == nullptr)
			return root;

		auto first = nodesInLevel.front();
		if (forLeft)
		{
			first->left = node;
			forLeft = false;
		}
		else
		{
			first->right = node;
			forLeft = true;
			nodesInLevel.pop();
		}
		if (node != nullptr)
			nodesInLevel.push(node);
	}
	return root;
}
