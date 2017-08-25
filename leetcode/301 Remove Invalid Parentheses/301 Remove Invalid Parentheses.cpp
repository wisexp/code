// 301 Remove Invalid Parentheses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> RemoveInvalidParentheses(string s)
{
	typedef pair<int, int> Range;
	vector<Range> ranges1, ranges2;

	int beg = 0;
	int left = 0, right = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(') left++;
		else if (s[i] == ')')
		{
			if (left > 0) left--;
			else right++;
		}

		if (right > 0)
		{
			ranges1.push_back({ beg, i });
			beg = i + 1;
			left = 0;
			right = 0;
		}
	}

	return {};
}


vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
	int row = A.size();
	int mid = A[0].size();
	int col = B[0].size();
	vector<vector<int>> ret(row, vector<int>(col, 0));
	vector<vector<pair<int, int>>> AA(row, vector<pair<int, int>>()), BB(col, vector<pair<int, int>>());
	for (int r = 0; r < row; r++)
	{
		for (int m = 0; m < mid; m++)
		{
			if (A[r][m] == 0) continue;
			AA[r].push_back({ m, A[r][m] });
		}
	}

	for (int c = 0; c < col; c++)
	{
		for (int m = 0; m < mid; m++)
		{
			if (B[m][c] == 0) continue;
			BB[c].push_back({ m, B[m][c] });
		}
	}

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (AA[r].empty() || BB[c].empty()) continue;

			int ia = 0, ib = 0;
			while (ia < AA[r].size() && ib < BB[c].size())
			{
				while (ia < AA[r].size() && ib < BB[c].size() && AA[r][ia].first != BB[c][ib].first)
				{
					if (AA[r][ia].first < BB[c][ib].first) ++ia;
					else if (AA[r][ia].first > BB[r][ib].first) ++ib;
				}
				if (ia < AA[r].size() && ib < BB[c].size())
					ret[r][c] += AA[r][ia].second * BB[c][ib].second;
				++ia;
				++ib;
			}
		}
	}
	return ret;
}

void PrintSparseMatrix(int row, int col)
{
	printf("[");
	for (int r = 0; r < row; r++)
	{
		printf("[");
		for (int c = 0; c < col; c++)
		{
			int v = rand() % 1000;
			printf("%d", v > 10 ? 0 : v);
			if (c != col - 1)
				printf(",");
		}
		printf("]");
		if (r != row - 1)
			printf(",");
	}
	printf("]\r\n");
}

int main()
{
	string s = ")(()))()()())";
	//auto ret = RemoveInvalidParentheses(s);

	int row = 15, mid = 1000, col = 15;

	PrintSparseMatrix(row, mid);
	PrintSparseMatrix(mid, col);

	vector<vector<int>> A = { {1,0,0}, {0,1,0}, {0,0,1} };
	vector<vector<int>> B = { { 1,0,0 },{ 0,1,0 },{ 0,0,1 } };
	//auto rr = multiply(A, B);
    return 0;
}

