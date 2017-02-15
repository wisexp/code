// BinarySearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <functional>


using namespace std;

int Search(int* arr, int n, int v)
{
    int l = 0, r = n - 1, m = (l + r) / 2;
    while (l <= r)
    {
        if (arr[m] == v) return m;
        if (arr[m] < v)
            l = m + 1;
        else
            r = m - 1;
        m = (l + r) / 2;
    }

    if (l == r) return n;
}

int main()
{
    int arr[1000];
    for (int i = 0; i < 1000; i++)
        arr[i] = i;
    auto ret = Search(arr, 1000, 34);
    return 0;
}

