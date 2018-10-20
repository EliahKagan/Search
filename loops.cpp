#include "loops.h"
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
        for(int i)
    }

}

void test_loops()
{
    vector a {10, 7, 3, 9, -4, 14, 27, 13, -27, 13, 17, 99, 103};
    vector b {"foo"s, "bar"s, "baz"s, "quux"s, "foobar"s};
}
