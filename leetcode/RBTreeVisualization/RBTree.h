#pragma once
#include <assert.h>
#include <functional>
#include <memory>
#include <set>
using namespace std;

class RBTree
{
public:
	struct Node;
	static std::function<void(Node* root)> DumpFn;

public:
	
	enum Color
	{
		Red,
		Black
	};

	struct Node
	{
		Node(int v, Node* left = nullptr, Node* right = nullptr)
		{
			this->left = left;
			this->right = right;
			val = v;
			if (left) left->parent = this;
			if (right) right->parent = this;
			color = Color::Red;
			this->parent = nullptr;
		}

		Node* left, *right, *parent;
		int val;
		Color color;
		int x, y;
		double offsetX, offsetY;
	};

	RBTree()
	{
		root = nullptr;
	}

	Node* GetRoot() const { return root; }

	// search v, return true if found. otherwise return false and the node that this value should be insert after.
	pair<bool, Node*> Find(int v)
	{
		return Find(GetRoot(), v);
	}

	bool Insert(int v)
	{
		Node* newNode = new Node(v);
		if (!root)
		{
			root = newNode;
			root->color = Color::Black;
			return true;
		}

		auto ret = Find(v);
		if (ret.first) return false;

		Insert(ret.second, newNode);
		return true;
	}

private:
	//Node* GrandParent(Node* node)
	//{
	//	return node->parent ? node->parent->parent : nullptr;
	//}

	//Node* Uncle(Node* node)
	//{
	//	auto grandParent = GrandParent(node);
	//	if (!grandParent)
	//		return nullptr;
	//	if (grandParent->left == node->parent)
	//		return grandParent->right;
	//	return grandParent->left;
	//}

	Node* Sibling(Node* node)
	{
		if (node->parent)
		{
			return node->parent->left == node ? node->parent->right : node->parent->left;
		}
		return nullptr;
	}

	void LeftRotate(Node* node)
	{
		// change node and rchild's position
		auto p = node->parent;
		auto r = node->right;
		if (p)
		{
			// r takes node's place (p->left or p->right)
			if (p->left == node)
				p->left = r;
			else
				p->right = r;
			r->parent = p;
		}
		else
		{
			root = r;
			r->parent = nullptr;
		}

		node->right = r->left;
		if (r->left) r->left->parent = node;
		r->left = node;
		node->parent = r;
	}

	void RightRotate(Node* node)
	{
		// change node and lchild's position
		auto p = node->parent;
		auto l = node->left;
		if (p)
		{
			// l takes node's place (p->left or p->right)
			if (p->right == node)
				p->right = l;
			else
				p->left = l;
			l->parent = p;
		}
		else
		{
			root = l;
			l->parent = nullptr;
		}

		node->left = l->right;
		if (l->right) l->right->parent = node;
		l->right = node;
		node->parent = l;
	}

	void UpdateColor(Node* node)
	{
		if (node->color == Color::Red)
		{
			if (!node->parent)
			{
				assert(node == root);
				// If it is root, then change color to black (height increase by 1)
				node->color = Color::Black;
			}
			else if (node->parent->color == Color::Black)
			{
				auto sibling = Sibling(node);
				if (sibling && sibling->color == Color::Red)
				{
					// Flip color.
					//                                   |
					//                      /\      ->  
					sibling->color = Color::Black;
					node->color = Color::Black;
					node->parent->color = Color::Red;
					UpdateColor(node->parent);
				}
				else if (node->parent->left == node)
				{
					// we are done. red is left child
					//                        
					//                      /  
				}
				else // if (node->parent->right == node)
				{
					// left rotate parent
					//                                             
					//                     \           ->         / 
					node->color = Color::Black;
					node->parent->color = Color::Red;
					LeftRotate(node->parent);
				}
			}
			else // if (node->parent->color == Color::Red)
			{
				assert(node->parent->parent); // a red node must have a parent.
				if (node->parent->left == node)
				{
					assert(node->parent->parent->color == Color::Black);
					assert(node->parent->color == Color::Red);
					// right rotate parent's parent, then flip color
					//                     /                                   |
					//                    /            ->         /\      ->  
					node->parent->color = Color::Black;
					node->parent->parent->color = Color::Red;
					RightRotate(node->parent->parent);
					UpdateColor(node);
				}
				else //if (node->parent->right == node)
				{
					// left rotate parent, then right roate parent's parent, then flip color
					//                     /                    /                                   |
					//                     \            ->     /            ->         /\      ->  
					auto oldNode = node->parent;
					LeftRotate(node->parent);
					UpdateColor(oldNode);
				}
			}
		}

		if (DumpFn)
		{
			DumpFn(root);
		}
	}

	void Insert(Node* parent, Node* newNode)
	{
		assert(parent->val != newNode->val);
		if (parent->val > newNode->val)
		{
			assert(parent->left == nullptr);
			parent->left = newNode;

		}
		else
		{
			assert(parent->right == nullptr);
			parent->right = newNode;
		}
		newNode->parent = parent;
		UpdateColor(newNode);
	}

	pair<bool, Node*> Find(Node* node, int v)
	{
		Node* prev = nullptr;;
		while (node)
		{
			prev = node;
			if (node->val == v) return{ true, node };
			if (node->val > v)
				node = node->left;
			else
				node = node->right;
		}
		return{ false, prev };
	}

	Node* root;
};

struct RBTreeTest
{
	static void Test()
	{
		array<int, 10> input;
		int k = 0;
		for (auto& i : input)
		{
			i = k++;
		}

		RBTree rbtree;
		for (auto& i : input)
		{
			auto result = rbtree.Insert(i);
			printf("insert %d, result %d\n", i, result);
		}
	}
};