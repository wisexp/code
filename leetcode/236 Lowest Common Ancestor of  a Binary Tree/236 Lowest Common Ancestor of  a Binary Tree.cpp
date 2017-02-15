// 236 Lowest Common Ancestor of  a Binary Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>

using namespace std;


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        list<TreeNode*> pathP, pathQ;

        if (Path(root, p, pathP) && Path(root, q, pathQ))
        {
            auto itP = pathP.begin();
            auto itQ = pathQ.begin();

            int dif = (int)(pathP.size()) - (int)(pathQ.size());

            if (dif > 0)
                advance(itP, dif);
            else if (dif < 0)
                advance(itQ, -dif);

            while (itP != pathP.end())
            {
                if ((*itP)->val == (*itQ)->val) return *itP;
                ++itP;
                ++itQ;
            }


        }

        return nullptr;

    }

    bool Path(TreeNode* root, TreeNode* node, list<TreeNode*>& path)
    {
        if (root == nullptr) return false;
        if (root->val == node->val)
        {
            path.push_back(root);
            return true;
        }

        auto result = Path(root->left, node, path);
        if (result)
        {
            path.push_back(root);
            return true;
        }

        result = Path(root->right, node, path);
        if (result)
        {
            path.push_back(root);
            return true;
        }
        return false;
    }
};
int main()
{

    TreeNode * root = new TreeNode(1);
    TreeNode * child = new TreeNode(2);
    TreeNode *c3 = new TreeNode(3);
    TreeNode *c4 = new TreeNode(4);
    root->right = child;
    child->left = c3;
    child->right = c4;
    Solution s;
    auto ret = s.lowestCommonAncestor(root, c3, c4);
    return 0;
}

