#include "pch.h"
#include "AStar.h"
#include <queue>
#include <unordered_set>
#include <set>
using namespace std;
#undef max
#undef min

namespace 
{
	vector<Position> GetNeighbours(double stepLength)
	{
		vector<Position> neighbours;
		int square = static_cast<int>(stepLength * stepLength);
		int step = static_cast<int>(stepLength);
		for (int i = -step; i <= step; i++)
		{
			for (int j = -step; j <= step; j++)
			{
				if (i == 0 && j == 0) continue;
				if (i * i + j * j <= square)
				{
					neighbours.push_back({ i,j });
				}
			}
		}
		return neighbours;
	}

	double Distance(Position p1, Position p2)
	{
		int dx = p1.first - p2.first;
		int dy = p1.second - p2.second;
		return sqrt(dx*dx + dy*dy);
	}
};

Node* AStarSearch::GetNode(Position pos, Position end)
{
	auto it = nodes.find(pos);
	if (it != nodes.end())
		return &it->second;
	Node node{};
	node.pos = pos;
	node.heuristicCost = Distance(pos, end);
	node.moveCost = numeric_limits<double>::max();
	nodes[pos] = node;
	return &nodes[pos];
}

struct NodeCompare
{
	bool operator()(const Node* left, const Node* right) const
	{
		return left->heuristicCost + left->moveCost < right->heuristicCost + right->moveCost;
	}
};

vector<Position> AStarSearch::FindPath(IDataSource* dataSource, Position begin, Position end, double stepLength)
{
	vector<Position> neighbours = GetNeighbours(stepLength);
	unordered_set<Position, PositionHash> closedCells;
	multiset<Node*, NodeCompare> openCells;

	auto current = GetNode(begin, end);
	current->moveCost = 0;
	openCells.insert(current);
	
	while (!openCells.empty())
	{
		current = *openCells.begin();
		openCells.erase(openCells.begin());
		if (current->pos == end)
		{
			break;
		}
		closedCells.insert(current->pos);
	
		for (auto pos : neighbours)
		{
			Position neighbour = current->pos;
			neighbour.first += pos.first;
			neighbour.second += pos.second;
			if (!dataSource->IsCellAvailable(neighbour))
				continue;
			if (closedCells.find(neighbour) != closedCells.end())
				continue;
			auto neighbourNode = GetNode(neighbour, end);			

			double moveCost = current->moveCost + Distance(current->pos, neighbourNode->pos);
			if (moveCost < neighbourNode->moveCost)
			{
				auto it = openCells.find(neighbourNode);
				if (it != openCells.end())
				{
					openCells.erase(it);
				}
				neighbourNode->moveCost = moveCost;
				neighbourNode->parent = current;
				openCells.insert(neighbourNode);
			}
		}

	}
	vector<Position> path;
	while (current->pos != begin)
	{
		path.push_back(current->pos);
		current = current->parent;
	}
	return path;
	
}


struct TestDataSource : IDataSource
{
	bool IsCellAvailable(Position pos) const override
	{
		if (pos.first < 0 || pos.first > 10) return false;
		if (pos.second < 0 || pos.second > 10) return false;
		if (pos.first == 5 && pos.second > 0 && pos.second < 9) return false;
		return true;
	}
};

void AStarSearchTest::Run()
{
	AStarSearch search;
	TestDataSource dataSource;
	auto path = search.FindPath(&dataSource, { 0,5 }, { 9,5 }, 5);
	int k = 0;
	k = k;
}