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
		double ret = sqrt(static_cast<double>(dx*dx + dy*dy));
		return ret;
	}
};

void AStarSearch::TakeSnapShot(SnapShotFunc snapshot)
{
	if (snapshot)
	{
		snapshot(closedCells, openCells, current);
	}
}

Node* AStarSearch::GetNode(Position pos, Position end)
{
	auto it = nodes.find(pos);
	if (it != nodes.end())
		return &it->second;
	Node node{};
	node.pos = pos;
	node.heuristicCost = Distance(pos, end) * 1.1;
	node.moveCost = numeric_limits<double>::max();
	node.kind = CellKind::Unknown;
	nodes[pos] = node;
	return &nodes[pos];
}

vector<Position> AStarSearch::FindPath(IDataSource* dataSource, Position begin, Position end, double stepLength, SnapShotFunc snapshot)
{
	vector<Position> neighbours = GetNeighbours(stepLength);

	current = GetNode(begin, end);
	current->moveCost = 0;
	openCells.insert(current);
	current->kind = CellKind::Open;
	TakeSnapShot(snapshot);
	while (!openCells.empty())
	{
		current = *openCells.begin();
		openCells.erase(openCells.begin());
		if (current->pos == end)
		{
			break;
		}
		closedCells.insert(current->pos);
		current->kind = CellKind::Closed;
	
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

			double moveCost = current->moveCost + (stepLength > 1.6 ? 1 : Distance(current->pos, neighbourNode->pos));
			if (moveCost < neighbourNode->moveCost)
			{
				auto itPair = openCells.equal_range(neighbourNode);
				for (auto it = itPair.first; it != itPair.second; ++it)
				{
					if ((*it)->pos == neighbourNode->pos)
					{
						openCells.erase(it);
						break;
					}
				}
				neighbourNode->moveCost = moveCost;
				neighbourNode->parent = current;
				neighbourNode->kind = CellKind::Open;
				openCells.insert(neighbourNode);
			}
		}
		TakeSnapShot(snapshot);

	}
	vector<Position> path;
	while (current->pos != begin)
	{
		path.push_back(current->pos);
		current = current->parent;
	}
	//TakeSnapShot(snapshot);
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