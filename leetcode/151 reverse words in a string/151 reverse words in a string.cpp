// 151 reverse words in a string.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

using namespace std;

class Solution {
    void Trim(string& s)
    {
        int i = 0, j = 0;
        char lastc = 0;
        while (i < s.size())
        {
            if (s[i] != ' ' ||
                lastc != ' ')
            {
                s[j] = s[i];
                j++;
            }
            lastc = s[i];
            i++;
        }

        auto beg = s.begin();
        auto end = beg + j;
        if (beg == end) s.clear();
        else if (beg + 1 == end && *beg == ' ') s.clear();
        else
        {
            if (*beg == ' ') ++beg;
            if (*(end - 1) == ' ') --end;
            s = string(beg, end);
        }
    }
public:
    void reverseWords(string &s) {
        Trim(s);
        if (s.empty()) return;
        auto beg = s.begin();

        auto end = s.end() -1;

        reverseWord(beg, end);

        while (beg < end)
        {
            auto temp = beg;
            while (*temp != ' ' && temp <= end) ++temp;

            reverseWord(beg, temp == end ? temp : temp - 1);

            while (*temp == ' ' && temp <= end) ++temp;
            beg = temp;
        }


    }

    void reverseWord(string::iterator beg, string::iterator end)
    {
        while (beg < end)
        {
            swap(*beg, *end);
            ++beg;
            --end;
        }
    }
};

int main()
{

    Solution s;
    string ss = "    a    b   ";
    s.reverseWords(ss);
    return 0;
}

