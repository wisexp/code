// 146 LRU Cache.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        auto it = index.find(key);
        if (it == index.end()) return -1;


        int v = it->second->second;
        set(key, v);
        return v;
    }

    void set(int key, int value) {
        auto it = index.find(key);
        bool updateRequired = true;
        if (it != index.end())
        {
            listValues.erase(it->second);
            index.erase(it);
            updateRequired = false;
        }

        listValues.push_front(make_pair(key, value));
        index.insert(make_pair(key, listValues.begin()));
        if (updateRequired)
            EraseIfFull();
    }

private:
    void EraseIfFull()
    {
        if (listValues.size() > cap)
        {
            auto last = listValues.end();
            --last;
            index.erase(last->first);
            listValues.erase(last);
        }
    }
    list<pair<int, int>> listValues;
    unordered_map<int, list<pair<int, int>>::iterator> index;
    int cap;

};
int main()
{
    LRUCache c(1);
    int ret = 0;
    c.set(2, 1);
    ret = c.get(2);
    c.set(3, 2);
    ret = c.get(2);
    ret = c.get(3);

    numeric_limits<int>::max()
    return 0;
}
