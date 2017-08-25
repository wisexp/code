// 592 FractionAddAndSubstraction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:
	string fractionAddition(string expression) {

		struct Fraction
		{
			int numerator;
			int denominator;
			Fraction(long n, long d) : numerator(n), denominator(d) {}
			static long gcd(long a, long b)
			{
				int sign = 1;
				if (a < 0) { sign *= -1; a = -a; }
				if (b < 0) { sign *= -1; b = -b; }
				return gcd2(a, b) * sign;
			}
			static long gcd2(long a, long b)
			{
				while (a >0 && b > 0)
				{
					if (a>b) a -= b;
					else b -= a;
				}
				if (a > 0) return a;
				return b;
			}

			Fraction& operator += (Fraction& rhs)
			{
				long d = denominator * rhs.denominator;
				if (d == 0)
				{
					numerator = 0;
					denominator = 1;
				}
				else
				{
					long n = numerator * rhs.denominator + denominator * rhs.numerator;
					long g = gcd(n, d);
					numerator = n / g;
					denominator = d / g;
				}
				return *this;
			}
			string tostring()
			{
				string result;
				int sign = 1;
				if (numerator < 0) { sign *= -1; numerator = -numerator; }
				if (denominator < 0) { sign *= -1; denominator = -denominator; }
				if (sign < 0) result.push_back('-');
				result += to_string(numerator);
				result += '/';
				result += to_string(denominator);
				return result;
			}
		};

		if (expression.size() == 0) return "0/1";
		int sign = 1;
		Fraction f(0, 1);
		int index = 0;
		while (index < expression.size())
		{
			if (expression[index] == '-')
			{
				sign = -1;
				index++;
			}
			else if (expression[index] == '+')
			{
				sign = 1;
				index++;
			}
			int n = 0;
			while (index < expression.size() && expression[index] != '/')
			{
				n = n * 10 + expression[index] - '0';
				index++;
			}
			index++;
			int d = 0;
			while (index < expression.size() && expression[index] != '+' && expression[index] != '-')
			{
				d = d * 10 + expression[index] - '0';
				index++;
			}

			Fraction r(n * sign, d);
			f += r;
		}

		return f.tostring();
	}
};

int main()
{
	Solution s;
	auto ret = s.fractionAddition("-1/2+1/2");
    return 0;
}

