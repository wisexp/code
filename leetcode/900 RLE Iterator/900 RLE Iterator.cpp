// 900 RLE Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

using namespace std;

class RLEIterator {
public:
	RLEIterator(const vector<int>& A) : a(A) {
		curIndex = 0;
		curCount = 0;
	}

	int next(int n) {
		do
		{
			if (curIndex >= a.size())
			{
				return -1;
			}
			else if (a[curIndex] >= curCount + n)
			{
				curCount += n;
				return a[curIndex + 1];
			}
			else
			{
				n -= a[curIndex] - curCount;
				curIndex += 2;
				curCount = 0;
			}
		} while (true);
	}
private:
	int curIndex;
	int curCount;
	const vector<int>& a;
};

/**
* Your RLEIterator object will be instantiated and called as such:
* RLEIterator obj = new RLEIterator(A);
* int param_1 = obj.next(n);
*/

int main()
{
	vector<int> s{ 3, 8, 0, 9, 2, 5 };
	RLEIterator it(s);
	int v = it.next(2);
    return 0;
}

