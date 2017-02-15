// 5 longest palindromic string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
    //typedef long long __int64;
public:
    string longestPalindrome(string s) {

        if (s.size() <= 1) return s;

        unordered_map<__int64, bool> flags;
        int ii = 0, jj = 0, len = 0;
        IsPalindrome(s, 0, s.size() - 1, flags, ii, jj, len);
        return s.substr(ii, len);
    }

private:
    __int64 To__int64(int i, int j)
    {
        __int64 res = i;
        res <<= 32;
        res += j;
        return res;
    }
    void ToInt(__int64 res, int&i, int&j)
    {
        j = res & 0xFFFF;
        i = res >> 32;
    }
    bool IsPalindrome(string& s, int i, int j, unordered_map<__int64, bool>& flags, int& ii, int& jj, int& len)
    {

        auto it = flags.find(To__int64(i, j));
        if (it != flags.end())
            return it->second;
        bool res = false;
        if (i == j)
            res = true;
        else if (i + 1 == j)
            res = s[i] == s[j];
        else
        {
            if (s[i] == s[j])
            {
                res = IsPalindrome(s, i + 1, j - 1, flags, ii, jj, len);
            }

            IsPalindrome(s, i + 1, j, flags, ii, jj, len);
            IsPalindrome(s, i, j - 1, flags, ii, jj, len);
        }

        flags.insert(make_pair(To__int64(i, j), res));
        if (res)
        {
            auto l = j - i + 1;
            if (l > len)
            {
                len = l;
                ii = i;
                jj = j;
            }
        }
        return res;
    }
};
int main()
{
    Solution s;
    string ss = "aaabaaaa";
    auto res = s.longestPalindrome(ss);
    return 0;
}

