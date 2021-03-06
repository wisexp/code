// 898 Bitwise ORs of Subarrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <set>

using namespace std;
class Solution {
public:
	int subarrayBitwiseORs(vector<int>& A) {
		int N = A.size();
		if (N <= 1) return N;
		vector<vector<int>> orResults(N, vector<int>(N));
		vector<vector<set<int>>> bitwiseResults(N, vector<set<int>>(N));
		for (int i = 0; i < N; i++)
		{
			orResults[i][i] = A[i];
			bitwiseResults[i][i].insert(A[i]);
		}

		for (int d = 1; d < N; d++)
		{
			for (int i = 0; i < N - d; i++)
			{
				orResults[i][i + d] = orResults[i][i + d - 1] | A[i + d];
				bitwiseResults[i][i + d] = bitwiseResults[i][i + d - 1];

				for (int k = 0; k <= d; k++)
				{
					bitwiseResults[i][i + d].insert(orResults[i+k][i + d]);
				}

			}
		}
		return bitwiseResults[0][N - 1].size();
	}
};

int main()
{
	Solution s;
	vector<int> v{ 1,2,4 };
	auto r = s.subarrayBitwiseORs(v);
    return 0;
}

