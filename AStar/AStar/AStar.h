#pragma once
#include <vector>
#include <unordered_map>

typedef std::pair<int, int> Position;
struct Node
{
	Position pos;
	Node* parent;
	double heuristicCost;
	double moveCost;
};

struct IDataSource
{
	virtual bool IsCellAvailable(Position pos) const = 0;
};

struct PositionHash
{
	unsigned operator()(Position pos) const
	{
		__int64 key = pos.first;
		key <<= 32;
		key += pos.second;
		return std::hash<__int64>()(key);
	}
};

class AStarSearch
{
public:
	std::vector<Position> FindPath(IDataSource* dataSource, Position begin, Position end, double stepLength);


private:

	Node* GetNode(Position pos, Position end);
	std::unordered_map<Position, Node, PositionHash> nodes;

};

class AStarSearchTest
{
public:
	void Run();
};