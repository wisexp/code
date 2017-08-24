#include "pch.h"
#include "AStar.h"
#include <algorithm>
#include <queue>
#include <map>
#include <set>
using namespace std;
AStar::AStar()
{
}


AStar::~AStar()
{
}

double Distance(Node* a, Node* b)
{
	auto dx = a->x - b->x;
	auto dy = a->y - b->y;
	return sqrt(static_cast<double>(dx*dx + dy*dy));
}



std::vector<Node*> AStar::FindPath(std::unordered_set<Node*, NodeHash>& map, Node* start, Node* end, double stepLength)
{
	//priority_queue<
	unordered_set<Node, NodeHash> closedSet;
	multimap<double, unordered_set<Node, NodeHash>>
	multiset<Node, NodeCompare> openSet;
	//priority_queue<Node, vector<Node>, NodeCompare> openSet;

	Node s;
	s.pos = start;
	s.moveCost = 0;
	s.heuristicCost = Distance(s.pos, end) / stepLength;
	openSet.insert(s);
	
	while (!openSet.empty())
	{
		Node top = *openSet.begin();
		openSet.erase(openSet.begin());
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				if (i == 0 && j == 0) continue;
				Node node;
				node.pos.x = top.pos.x + i;
				node.pos.y = top.pos.y + j;
				if (closedSet.find(node) == closedSet.end())
				{
					auto it = map.find(node.pos);
					if (it != map.end() && it->second)
					{
						auto range = openSet.find()
					}
				}
			}
		}
	}
}
