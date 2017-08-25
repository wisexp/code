// 381 RandomizedCollection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedCollection {
public:
	/** Initialize your data structure here. */
	RandomizedCollection() {

	}

	/** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
	bool insert(int val) {
		nums.push_back(val);

		auto it = hm.find(val);
		if (it != hm.end())
		{
			it->second.push_back(nums.size() - 1);
			return false;
		}
		else
		{
			vector<int> vvv{ static_cast<int>(nums.size() - 1) };

			hm.insert({ val, vvv });
			return true;
		}
	}

	/** Removes a value from the collection. Returns true if the collection contained the specified element. */
	bool remove(int val) {
		auto it = hm.find(val);
		if (it == hm.end()) return false;
		auto index = it->second.back();
		it->second.pop_back();
		if (it->second.empty()) hm.erase(it);

		if (index == static_cast<int>(nums.size() - 1))
		{
			nums.pop_back();
		}
		else
		{
			int target = nums[nums.size() - 1];
			nums[index] = target;
			

			it = hm.find(target);
			for (auto& i : it->second)
			{
				if (i == static_cast<int>(nums.size() - 1))
				{
					i = index;
					break;
				}
			}

			nums.pop_back();
		}

		return true;

	}

	/** Get a random element from the collection. */
	int getRandom() {
		if (nums.size() == 1) return nums[0];
		return nums[rand() % (nums.size() - 1)];
	}
	vector<int> nums;
	unordered_map<int, vector<int /*index*/>> hm;
};


int main()
{
	RandomizedCollection rc;
	rc.insert(1);
	rc.insert(1);
	rc.insert(2);
	rc.insert(1);
	rc.insert(2);
	rc.insert(2);

	rc.remove(1);
	rc.remove(2);
	rc.remove(2);
	rc.remove(2);
	for (int i = 0; i < 10; i++)
	{
		int v = rc.getRandom();

		printf("%d\r\n", v);
	}
    return 0;
}

