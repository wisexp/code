// 283 Move Zeroes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
using namespace std;

int MoveZeroes(vector<int>& nums)
{
	int size = nums.size();
	int i = 0, j = 0;
	int count = 0;
	while (j < size)
	{
		while (j < size && nums[j] == 0) j++;
		if (j == size) break;
		if (nums[i] == 0)
		{
			swap(nums[i], nums[j]);
			count++;
		}
		i++;
		j++;
	}
	return count;
}

int MoveZeroes2(vector<int>& nums) {
	int last = 0, cur = 0;
	int count = 0;
	while (cur < nums.size()) {
		if (nums[cur] != 0) {
			swap(nums[last], nums[cur]);
			count++;
			last++;
		}

		cur++;
	}
	return count;
}

int main()
{
	vector<int> input(10);
	for (int i = 0; i < input.size(); i++)
	{
		input[i] = rand() % 1000;
		//if (input[i] % 20 == 0) input[i] = 0;
	}
	input.back() = 0;
	vector<int> copy(input);

	int count = MoveZeroes(copy);

	copy = input;
	count = MoveZeroes2(copy);
    return 0;
}

