// 273 Integer to English Words.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Utils\LeetCodeUtils.h"

class Solution {
public:

	string numberToWords(int num) {
		if (num == 0) return "Zero";
		vector<string> ones = {"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine " };
		vector<string> tens = { "", "", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety " };
		vector<string> teens = { "Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen " };
		vector<string> thousands = { "", "Thousand ", "Million ", "Billion " };

		
		int k = 0;
		
		string f;
		while (num > 0)
		{
			string ret;
			int n = num % 1000;
			num /= 1000;

			if (n >= 100)
			{
				ret += ones[n / 100];
				ret += "Hundred ";
				n %= 100;
			}
			if (n >= 20)
			{
				ret += tens[n / 10];
				n %= 10;
			}
			
			if (n >= 10)
			{
				ret += teens[n - 10];
			}
			else
				ret += ones[n];
			f = ret + thousands[k] + f;
			k++;
		}
		f.pop_back();
		return f;
	}
};

int main()
{
	Solution s;
	auto ret = s.numberToWords(12345);
    return 0;
}

