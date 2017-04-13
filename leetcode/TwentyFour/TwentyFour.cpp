// TwentyFour.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
using namespace std;

struct Fraction
{
	Fraction(int numerator, int denominator = 1)
		: numerator(numerator)
		, denominator(denominator)
	{		
		error = denominator == 0;
	}

	Fraction operator+(const Fraction& rhs) const
	{
		return Fraction(numerator * rhs.denominator + denominator * rhs.numerator, denominator * rhs.denominator);
	}

	Fraction operator-(const Fraction& rhs) const
	{
		return operator+(Fraction(-rhs.numerator, rhs.denominator));
	}

	Fraction operator*(const Fraction& rhs) const
	{
		return Fraction(numerator * rhs.numerator, denominator * rhs.denominator);
	}

	Fraction operator/(const Fraction& rhs) const
	{
		return Fraction(numerator * rhs.denominator, denominator * rhs.numerator);
	}

	bool operator==(const Fraction& rhs) const
	{
		return !error && !rhs.error && numerator * rhs.denominator == denominator * rhs.numerator;
	}
	bool operator!= (const Fraction& rhs) const
	{
		return !operator==(rhs);
	}
	bool operator==(int v) const
	{
		return !error && denominator * v == numerator;
	}
	bool operator != (int v) const
	{
		return !operator==(v);
	}

	int numerator;
	int denominator;
	bool error;
};

vector<Fraction> Compute(Fraction a, Fraction b)
{
	vector<Fraction> result;
	result.emplace_back(a + b);
	result.emplace_back(a - b);
	result.emplace_back(b - a);
	result.emplace_back(a * b);
	if (a != 0) result.emplace_back(b / a);
	if (b != 0) result.emplace_back(a / b);
	return result;
}

bool Check(vector<Fraction>& nums, Fraction target)
{
	if (nums.size() == 1) return nums[0] == target;

	for (int i = 0; i < nums.size(); i++)
	{
		auto temp = nums;
		temp.erase(temp.begin() + i);
		auto targets = Compute(nums[i], target);
		for (auto& t : targets)
			if (Check(temp, t)) 
				return true;
	}

	return false;
}

bool Check(vector<int>& nums, int target)
{
	vector<Fraction> temp;
	for (auto i : nums)
		temp.push_back(i);
	return Check(temp, target);
	
}

int main(int argc, char* argv[])
{
	if (argc == 6)
	{
		vector<int> nums;
		for (int i = 0; i < 4; i++)
		{
			nums.push_back(atoi(argv[i + 1]));
		}
		int target = atoi(argv[5]);
		auto result = Check(nums, target);

		printf("result = %s\r\n", result ? "true" : "false");
		return 0;
	}
	printf("TwentyFour 1 2 3 4 24\r\n");
    return 0;
}

