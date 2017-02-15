// 159 lengthOfLongestSubstringTwoDistinct.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <algorithm>
using namespace std;
class Solution {
public:


    int lengthOfLongestSubstringTwoDistinct(string s) {
        char dict[2] = { 0,0 };
        int count[2] = { 0,0 };

        int i = 0, j = 0;
        int m = 0;
        for (j = 0; j < s.size(); j++)
        {
            char c = s[j];
            bool found = true;
            do
            {
                found = true;

                if (dict[0] == c)
                {
                    count[0]++;
                }
                else if (dict[1] == c)
                {
                    count[1]++;
                }
                else if (dict[0] == 0)
                {
                    dict[0] = c;
                    count[0]++;
                }
                else if (dict[1] == 0)
                {
                    dict[1] = c;
                    count[1]++;
                }
                else
                {
                    found = false;
                    while (i < j)
                    {
                        char begin = s[i];
                        i++;
                        if (dict[0] == begin)
                        {
                            count[0]--;
                            if (count[0] == 0)
                            {
                                dict[0] = 0;
                                
                                break;
                            }
                        }
                        else if (dict[1] == begin)
                        {
                            count[1]--;
                            if (count[1] == 0)
                            {
                                dict[1] = 0;
                                
                                break;
                            }
                        }
                        else
                        {
                            return -1;
                        }
                        
                    }
                }
            } while (!found);
            m = max(j - i, m);
        }

        return m + 1;
    }
};
int main()
{

    Solution s;
    auto l = s.lengthOfLongestSubstringTwoDistinct("ecebakdfjwlkjwekljasddlkasdfkljasdffkljasgadsfsdssdsdssdffssdfa");
    return 0;
}

