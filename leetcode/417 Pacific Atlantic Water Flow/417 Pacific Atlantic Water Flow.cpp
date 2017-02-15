// 417 Pacific Atlantic Water Flow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <queue>
#include <iostream>

using namespace std;

struct Data
{
	Data(int v, int r, int c)
		: v(v)
		, r(r)
		, c(c)
	{

	}
	int v;
	int r;
	int c;

	bool operator< (const Data& rhs) const
	{
		return v > rhs.v;
	}

	void Dump() const
	{
		printf("%d, %d, %d\r\n", v, r, c);
		//cout << v << ', ' << r << ', ' << c << endl;
	}
};

int main()
{
	priority_queue<Data> q;
	q.push(Data(1, 2, 3));
	q.push(Data(2, 1, 2));
	q.push(Data(2, 1, 3));
	q.push(Data(1, 1, 3));
	q.push(Data(3, 1, 1));

	while (!q.empty())
	{
		q.top().Dump();
		q.pop();
	}
    return 0;
}

