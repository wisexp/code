#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Node
{
	int x;
	int y;
	bool canPass;
	double heuristicCost;
	double moveCost;
	Node* parent;
};


struct NodeHash
{
	unsigned operator()(const Node* node) const
	{
		__int64 key = node->x;
		key = (key >> 32) + node->y;
		return std::hash<__int64>()(key);
	}
};


struct NodeCompare
{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return lhs->heuristicCost + lhs->moveCost < rhs->heuristicCost + rhs->moveCost;
	}
};


class AStar
{
public:
	AStar();
	~AStar();
	std::vector<Node*> FindPath(std::unordered_set<Node*, NodeHash>& map, Node* start, Node* end, double stepLength);
};

