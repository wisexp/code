// 909. Snakes and Ladders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:

	pair<int, int> PtFromIndex(int n, int N)
	{
		int r = N - 1 - n / N;
		int c = n % N;
		if ((N - 1 - r) % 2 == 1)
			c = N - 1 - c;
		return make_pair(r, c);
	}

	int snakesAndLadders(vector<vector<int>>& board) 
	{
		int N = board.size();
		vector<bool> visited(N*N, false);
		queue<int> path;
		int start = 0;
		path.push(start);
		int step = 0;
		while (!path.empty())
		{
			auto size = path.size();
			for (int s = 0; s < size; s++)
			{
				auto cur = path.front();
				path.pop();
				visited[cur] = true;

				if (cur == N * N - 1)
					return step;

				for (int i = 1; i <= 6; i++)
				{
					auto next = cur + i;
					if (next >= N * N) break;

					const auto& nextPt = PtFromIndex(next, N);

					auto v = board[nextPt.first][nextPt.second];
					if (v == -1)
					{
						if (visited[next]) continue;
						visited[next] = true;
						path.push(next);
					}
					else
					{
						auto jump = v - 1;
						if (!visited[jump])
							path.push(jump);
					}
				}
			}
			step++;
		}

		return -1;

	}
};

int main()
{
	vector<vector<int>> board =
		//{ { -1,-1,-1,-1,-1,-1 },{ -1,-1,-1,-1,-1,-1 },{ -1,-1,-1,-1,-1,-1 },{ -1,35,-1,-1,13,-1 },{ -1,-1,-1,-1,-1,-1 },{ -1,15,-1,-1,-1,-1 } };
	{ { -1,-1,-1,30,-1,144,124,135,-1,-1,-1,-1,-1 },{ -1,-1,-1,-1,-1,-1,167,93,-1,-1,-1,-1,-1 },{ -1,-1,-1,-1,-1,-1,-1,77,-1,-1,90,-1,-1 },{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,122,-1 },{ -1,-1,-1,23,-1,-1,-1,-1,-1,155,-1,-1,-1 },{ -1,-1,140,29,-1,-1,-1,-1,-1,-1,-1,-1,-1 },{ -1,-1,-1,-1,-1,115,-1,-1,-1,109,-1,-1,5 },{ -1,57,-1,99,121,-1,-1,132,-1,-1,-1,-1,-1 },{ -1,48,-1,-1,-1,68,-1,-1,-1,-1,31,-1,-1 },{ -1,163,147,-1,77,-1,-1,114,-1,-1,80,-1,-1 },{ -1,-1,-1,-1,-1,57,28,-1,-1,129,-1,-1,-1 },{ -1,-1,-1,-1,-1,-1,-1,-1,-1,87,-1,-1,-1 } };
	Solution s;
	auto ret = s.snakesAndLadders(board);
    return 0;
}

