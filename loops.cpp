#include "loops.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::literals;

namespace {
    template <typename T>
    T range_for(const vector<T> &a)
    {
        T result {};
        for(auto &i: a)
            result += i;
        return result;
    }

    template <typename T>
    T typical_for(const vector<T> &a)
    {
        T result {};
        for (auto i = a.begin(); i != a.end(); ++i)
            result += *i;
        return result;
    }

    template <typename T>
    T for_indices(const vector<T> &a)
    {
        T result {};
        for(int i = 0; i < (a.end()-a.begin()); ++i)
            result += a[i];
        return result;
    }

    template <typename T>
    T for_indices_size(const vector<T> &a)
    {
        T result {};
        for(int i = 0; i < a.size(); ++i)
            result += a[i];
        return result;
    }

    template <typename T>
    T for_each_test(const vector<T> &a)
    {
        for_each(a.begin(), a.end(),
    }

}

void test_loops()
{
    vector a {10, 7, 3, 9, -4, 14, 27, 13, -27, 13, 17, 99, 103};
    vector b {"foo"s, "bar"s, "baz"s, "quux"s, "foobar"s};
}
