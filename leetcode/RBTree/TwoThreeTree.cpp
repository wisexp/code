#include "stdafx.h"
#include "TwoThreeTree.h"
#include "stdafx.h"
#include <map>
#include <stdexcept>
#include <exception>
#include <assert.h>
#include <array>
#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
using namespace std;
enum Type
{
	_2,
	_3,
	_4,
};
struct _23Tree
{
	_23Tree(int v, _23Tree* child1 = nullptr, _23Tree* child2 = nullptr)
	{
		values[0] = v;
		type = Type::_2;
		values[1] = 0;
		children[0] = child1;
		children[1] = child2;
		children[2] = nullptr;
		children[3] = nullptr;
		parent = nullptr;
		if (child1) child1->parent = this;
		if (child2) child2->parent = this;
	}
	_23Tree(int v1, int v2, _23Tree* child1 = nullptr, _23Tree* child2 = nullptr, _23Tree* child3 = nullptr)
	{
		values[0] = v1;
		type = Type::_3;
		values[1] = v2;
		children[0] = child1;
		children[1] = child2;
		children[2] = child3;
		children[3] = nullptr;
		parent = nullptr;
		if (child1) child1->parent = this;
		if (child2) child2->parent = this;
		if (child3) child3->parent = this;
	}


	Type type;
	int values[3];
	_23Tree* children[4];
	_23Tree* parent;
};


const int Width = 220;
void DumpNode(array<char, Width>& buffer, _23Tree* node, int level, int group)
{
	//if (!node) return;
	const int maxLevel = 3;
	const int gLen = 4;
	int g = pow(3, (maxLevel - level));
	int totalG = pow(3, level);
	int gOffset = g * (group - totalG / 2 - 1);

	int offset = gOffset * gLen + buffer.size() / 2;
	if (node)
	{
		buffer[offset++] = '@';
		if (node->type == Type::_3)
			buffer[offset] = '@';
	}
	else
	{
		//buffer[offset] = 'E';
	}
}

void Visit(_23Tree* root)
{
	int level = 0;
	queue<_23Tree*> q;
	q.push(root);
	int expectedCount = 1;
	array<char, Width> buffer;
	for (auto& c : buffer)
		c = ' ';
	int count = 0;
	bool hasValue = false;
	while (!q.empty())
	{
		auto node = q.front();
		q.pop();
		//if (node == nullptr) break;
		count++;
		DumpNode(buffer, node, level, count);
		if (node)
		{
			q.push(node->children[0]);
			q.push(node->children[1]);
			q.push(node->children[2]);
			hasValue = true;
		}
		else
		{
			q.push(nullptr);
			q.push(nullptr);
			q.push(nullptr);
		}
		if (count == expectedCount)
		{
			if (!hasValue) break;
			expectedCount *= 3;
			count = 0;
			level++;
			buffer[buffer.size() - 1] = 0;
			printf("%s\r\n", buffer.data());
			hasValue = false;
			for (auto& c : buffer)
				c = ' ';
		}
	}
}

// Search in 23 Tree, return true and the node if v is found
// otherwise return false and the node which indicts the node 
// the v should be inserted into.
pair<bool, _23Tree*> Find(_23Tree* node, int v)
{
	if (node->type == Type::_2)
	{
		if (node->values[0] == v)
			return{ true, node };
		else if (node->values[0] < v && node->children[1])
			return Find(node->children[1], v);
		else if (node->values[0] > v && node->children[0])
			return Find(node->children[0], v);
		return{ false, node };
	}
	else if (node->type == Type::_3)
	{
		if (node->values[0] == v || node->values[1] == v)
			return{ true, node };
		else if (node->values[0] > v && node->children[0])
			return Find(node->children[0], v);
		else if (node->values[1] > v && node->children[1])
			return Find(node->children[1], v);
		else if (node->values[1] < v && node->children[2])
			return Find(node->children[2], v);
		return{ false, node };
	}
	assert(false);
}

// split a 4-node into two 2-nodes (ref paramenters), and the mid value (return value)
int FourNodeSplit(_23Tree* node, _23Tree*& left, _23Tree*& right)
{
	assert(node->type == Type::_4);
	int v = node->values[1];

	right = new _23Tree(node->values[2], node->children[2], node->children[3]);
	left = node;
	left->type = Type::_2;
	left->children[2] = nullptr;
	left->values[1] = -1;
	return v;
}

// push two 2-nodes and value up to a 2-node, to form a 3-node.
void TwoNodeAccept(_23Tree* node, int v, _23Tree* left, _23Tree* right)
{
	assert(node->type == Type::_2);
	node->type = Type::_3;
	if (node->values[0] < v)
	{
		assert(node->children[1] == left);
		//node->children[1] = left;
		node->children[2] = right;
		node->values[1] = v;
	}
	else
	{
		assert(node->children[0] == left);
		node->children[2] = node->children[1];
		//node->children[0] = left;
		node->children[1] = right;
		node->values[1] = node->values[0];
		node->values[0] = v;
	}
	assert(left->parent == node);
	//left->parent = node;
	right->parent = node;
}

// push two 2-nodes and value up to a 3-node, to form a 4-node.
void ThreeNodeAccept(_23Tree* node, int v, _23Tree* left, _23Tree* right)
{
	assert(node->type == Type::_3);
	node->type = Type::_4;
	if (node->values[0] > v)
	{
		assert(node->children[0] == left);
		node->children[3] = node->children[2];
		node->children[2] = node->children[1];
		//node->children[0] = left;
		node->children[1] = right;
		node->values[2] = node->values[1];
		node->values[1] = node->values[0];
		node->values[0] = v;
	}
	else if (node->values[1] > v)
	{
		assert(node->children[1] == left);
		node->children[3] = node->children[2];
		//node->children[1] = left;
		node->children[2] = right;
		node->values[2] = node->values[1];
		node->values[1] = v;
	}
	else
	{
		assert(node->children[2] == left);
		//node->children[2] = left;
		node->children[3] = right;
		node->values[2] = v;
	}
	assert(left->parent == node);
	left->parent = node;
	right->parent = node;
}

// adjust 4-node, split it and push up
void Promote(_23Tree*& root, _23Tree* node)
{
	assert(node->type == Type::_4);
	_23Tree* left, *right;
	int v = FourNodeSplit(node, left, right);
	if (!node->parent)
	{
		// 4-node on root, increase one level and return a new root.
		root = new _23Tree(v, left, right);
	}
	else
	{
		if (node->parent->type == Type::_2)
		{
			// change parent from 2-node to 3-node
			TwoNodeAccept(node->parent, v, left, right);
		}
		else //if (node->parent->type == Type::_3)
		{
			// change parent from 3-node to 4-node
			ThreeNodeAccept(node->parent, v, left, right);
			// recursively promote 4-node parent
			Promote(root, node->parent);
		}
	}
}

bool Insert(_23Tree*& root, int v, _23Tree* node = nullptr /*hint*/)
{
	if (root == nullptr)
	{
		root = new _23Tree(v);
		return true;
	}
	if (!node)
	{
		auto ret = Find(root, v);
		assert(!ret.first);
		node = ret.second;
	}
	assert(node);
	if (node->type == Type::_2)
	{
		if (node->values[0] == v)
			return false;
		if (node->values[0] > v && node->children[0] != nullptr)
			return Insert(root, v, node->children[0]);
		if (node->values[0] < v && node->children[1] != nullptr)
			return Insert(root, v, node->children[1]);

		node->type = Type::_3;
		if (node->values[0] > v)
		{
			node->values[1] = node->values[0];
			node->values[0] = v;
			node->children[2] = node->children[1];
			node->children[1] = node->children[0];
			node->children[0] = nullptr;
		}
		else // if (node->values[0] < v)
		{
			node->values[1] = v;
			node->children[2] = nullptr;
		}
	}
	else // if (node->type == Type::_3)
	{
		if (node->values[0] == v || node->values[1] == v)
			return false;
		if (node->values[0] > v && node->children[0] != nullptr)
			return Insert(root, v, node->children[0]);
		if (node->values[0] < v && node->values[1] > v && node->children[1] != nullptr)
			return Insert(root, v, node->children[1]);
		if (node->values[1] < v && node->children[2] != nullptr)
			return Insert(root, v, node->children[2]);

		for (int i = 0; i < 3; i++)
			assert(node->children[i] == nullptr);

		node->type = Type::_4;
		if (node->values[0] > v)
		{
			node->values[2] = node->values[1];
			node->values[1] = node->values[0];
			node->values[0] = v;
		}
		else if (node->values[1] > v)
		{
			node->values[2] = node->values[1];
			node->values[1] = v;
		}
		else
		{
			node->values[2] = v;
		}
		Promote(root, node);
	}

	return true;
}


typedef array<int, 30> Input;
void Visualize(Input arr)
{
	_23Tree* root = nullptr;
	for (int i = 0; i < arr.size(); i++)
	{
		auto ret = Insert(root, arr[i]);
		system("cls");
		printf("insert %d, result %d\n", arr[i], ret);
		Visit(root);
		getchar();
	}
}
namespace TwoThreeTree
{
	void Test()
	{
		Input arr;
		for (int i = 0; i < arr.size(); i++)
		{
			arr[i] = 100 - i;
		}

		//	set<int> ss(arr.begin(), arr.end());
		Visualize(arr);

		std::random_shuffle(arr.begin(), arr.end());
		Visualize(arr);

		std::sort(arr.begin(), arr.end());
		Visualize(arr);
	}
}