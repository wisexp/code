// TreeWalker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node
{
    Node* left;
    Node* right;
    int val;

    Node(int v = 0, Node* l = nullptr, Node* r = nullptr)
        : val(v), left(l), right(r)
    {}
};

using Visitor = std::function<void(Node*)>;
void PreOrder(Node* root, Visitor visitor)
{
    if (root)
    {
        visitor(root);
        PreOrder(root->left, visitor);
        PreOrder(root->right, visitor);
    }
}

void PreOrderIterative(Node* root, Visitor visitor)
{
    std::stack<Node*> q;
    q.push(root);

    while (!q.empty())
    {
        auto cur = q.top();
        q.pop();
        visitor(cur);
        if (cur->right) q.push(cur->right);
        if (cur->left) q.push(cur->left);
    }
}

void InOrder(Node* root, Visitor visitor)
{
    if (root)
    {
        InOrder(root->left, visitor);
        visitor(root);
        InOrder(root->right, visitor);
    }
}

void InOrderIterative(Node* root, Visitor visitor)
{
    stack<Node*> st;
    auto cur = root;
    
    while (true)
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        if (!st.empty())
        {
            auto p = st.top();
            st.pop();
            visitor(p);
            cur = p->right;
        }
        else
            break;
    }
}

void PostOrder(Node* root, Visitor visitor)
{
    if (root)
    {
        PostOrder(root->left, visitor);
        PostOrder(root->right, visitor);
        visitor(root);
    }
}

void PostOrderIterative(Node* root, Visitor visitor)
{
    stack<Node*> st;
    auto cur = root;
    Node* last = nullptr;

    while (true)
    {
        while (cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        if (!st.empty())
        {
            auto p = st.top();
            if (p->right && last != p->right)
            {
                cur = p->right;
            }
            else
            {
                st.pop();
                visitor(p);
                last = p;
            }
        }
        else
            break;
    }
}

void ByLevel(Node* root, Visitor visitor)
{
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    int countInLastLevel = 1;
    int countInThisLevel = 0;
    int count = 0;
    while (!q.empty())
    {
        auto p = q.front();
        visitor(p);
        q.pop();
        count++;

        if (p->left) { q.push(p->left); countInThisLevel++; }
        if (p->right) { q.push(p->right); countInThisLevel++; }

        if (count == countInLastLevel)
        {
            count = 0;
            countInLastLevel = countInThisLevel;
            countInThisLevel = 0;
            cout << endl;
        }
    }
}

Node* BuildTree()
{
    Node* root = new Node(1);    
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7, new Node(8), new Node(9, nullptr, new Node(10)));

    return root;
}

auto visitor = [](Node* node)
{
    cout << node->val << '\t';
};

void TestPreOrder()
{
    auto root = BuildTree();
    PreOrder(root, visitor);

    cout << endl;

    PreOrderIterative(root, visitor);

    cout << endl;

    InOrder(root, visitor);

    cout << endl;

    InOrderIterative(root, visitor);

    cout << endl;

    PostOrder(root, visitor);

    cout << endl;

    PostOrderIterative(root, visitor);

    cout << endl;

    ByLevel(root, visitor);

    cout << endl;
}


int main()
{
    TestPreOrder();
    return 0;
}

