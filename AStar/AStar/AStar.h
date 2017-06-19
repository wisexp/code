#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

typedef std::pair<int, int> Position;

enum class CellKind
{
	Unknown,
	Open,
	Closed
};

struct Node
{
	Position pos;
	Node* parent;
	double heuristicCost;
	double moveCost;
	CellKind kind;
};

struct IDataSource
{
	virtual bool IsCellAvailable(Position pos) const = 0;
};




struct CellInfo
{
	CellInfo()
	{
		isAvailable = true;
		kind = CellKind::Unknown;
		isOnCurrentPath = false;
		parent.first = -1;
		parent.second = -1;
		moveCost = -1;
		heuristicCost = -1;
	}
	bool isAvailable;
	CellKind kind;
	bool isOnCurrentPath;
	Position parent;
	double moveCost;
	double heuristicCost;
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


struct NodeCompare
{
	bool operator()(const Node* left, const Node* right) const
	{
		
		double l = left->heuristicCost + left->moveCost;
		double r = right->heuristicCost + right->moveCost;
		if (l < r) return true;
		if (l == r) return left->heuristicCost < right->heuristicCost;
		return false;
	}
};


typedef std::function<void (std::unordered_set<Position, PositionHash>& closedCells, std::multiset<Node*, NodeCompare>& openCells, Node* current)> SnapShotFunc;
class AStarSearch
{
public:
	std::vector<Position> FindPath(IDataSource* dataSource, Position begin, Position end, double stepLength, SnapShotFunc snapshot = nullptr);


private:
	void TakeSnapShot(SnapShotFunc snapshot = nullptr);
	Node* GetNode(Position pos, Position end);
	std::unordered_map<Position, Node, PositionHash> nodes;
	Node* current;
	std::unordered_set<Position, PositionHash> closedCells;
	std::multiset<Node*, NodeCompare> openCells;

};

class AStarSearchTest
{
public:
	void Run();
};