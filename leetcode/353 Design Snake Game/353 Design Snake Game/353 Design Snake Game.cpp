// 353 Design Snake Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

namespace std {
    template <>
    struct hash<pair<int, int>> : _Bitwise_hash<pair<int, int>>
    {

    };
}
class SnakeGame {
public:
    /** Initialize your data structure here.
    @param width - screen width
    @param height - screen height
    @param food - A list of food positions
    E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food)
        : W(width)
        , H(height)
        , F(food)
    {
        SI.push(S.insert(make_pair(0, 0)).first);
    }

    /** Moves the snake.
    @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
    @return The game's score after the move. Return -1 if game over.
    Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {

        if (direction.size() != 1) return -2;
        char d = direction[0];
        if (d >= 'A' && d <'Z') d = d + 'a' - 'A';
        int dx = 0, dy = 0;
        switch (d)
        {
        case 'u': dy = -1; break;
        case 'd': dy = 1; break;
        case 'l': dx = -1; break;
        case 'r': dx = 1; break;
        default: return -2;
        }
        int length = SI.size();
        auto head = *(SI.back());
        auto newHead = make_pair(head.first + dx, head.second + dy);
        if (newHead.first <0 || newHead.first >= W || newHead.second <0 || newHead.second >= H) return -1;
        if (S.find(newHead) != S.end()) return -1;
        SI.push(S.insert(newHead).first);
        if (newHead == F[length - 1]) // grow
        {
            return length + 1;
        }
        else
        {
            auto it = SI.front();
            SI.pop();
            S.erase(it);
            return length;
        }
    }

private:
    struct MyHash
    {
        size_t operator()(const pair<int, int>& p) const
        {
            return p.first + p.second;
        }
    };
    int W, H;
    unordered_set<pair<int, int>, MyHash> S;
   
    queue<unordered_set<pair<int, int>>::iterator> SI;

    vector<pair<int, int>> F;
};

/**
* Your SnakeGame object will be instantiated and called as such:
* SnakeGame obj = new SnakeGame(width, height, food);
* int param_1 = obj.move(direction);
*/


class Solution {
public:
    void reverseWords(string &s) {

        if (s.empty()) return;
        auto beg = s.begin();
        
        auto end = s.end();
        while (*beg == ' ') ++beg;
        --end;
        while (*end == ' ') --end;
        auto begin = beg;
        reverseWord(beg, end);

        while (beg < end)
        {
            auto temp = beg;
            while (*temp != ' ') ++temp;

            reverseWord(beg, temp - 1);

            while (*temp == ' ' && temp <= end) ++temp;
            beg = temp;
        }

        // trim

        string t;
        t.reserve(end - begin);
        char lastc = 0;
        for (auto b = begin; b <= end; b++)
        {
            if (*b == ' ' && lastc == ' ')
                continue;
            t.push_back(*b);
            lastc = *b;

        }
        t.swap(s);
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
    Solution ss;
    string s = "+---...2x+--x--+x-+-x2...---+";
    ss.reverseWords(s);
    int k = 0;
    //vector<pair<int, int>> F;
    //F.push_back(make_pair(1, 2));
    //F.push_back(make_pair(0,1));
    //
    //SnakeGame s(3,2,F);
    //int ret;
    //ret = s.move("R");
    //ret = s.move("D");
    //ret = s.move("R");
    //ret = s.move("U");
    //ret = s.move("L");
    //ret = s.move("U");
    return 0;
}

