#include "loops.h"

#include <algorithm>
#include <complex>
#include <iostream>
#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;
using namespace std::literals;

namespace {
    template <typename T>
    T using_accumulate(const vector<T> &a)
    {
        return accumulate(a.begin(), a.end(), T{});
    }

    template <typename T>
    T for_each_test(const vector<T> &a)
    {
        T result {};
        for_each(a.begin(), a.end(), [&result](const T &t){result += t;});
        return result;
    }

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

    template<typename T>
    constexpr bool same(const T&) noexcept
    {
        return true;
    }

    template<typename T, typename U, typename... Vs>
    constexpr bool same(const T& x, const U& y, const Vs&... zs)
    {
        static_assert(is_same_v<T, U>);
        return x == y && same(y, zs...);
    }

    template<typename T>
    void test(const vector<T>& a)
    {
        const auto s1 = using_accumulate(a);
        const auto s2 = for_each_test(a);
        const auto s3 = range_for(a);
        const auto s4 = typical_for(a);
        const auto s5 = for_indices(a);
        const auto s6 = for_indices_size(a);

        cout << "Sum = " << s1 << ". Checks out? "
             << same(s1, s2, s3, s4, s5, s6) << '\n';
    }
}

void test_loops()
{
    vector a {10, 7, 3, 9, -4, 14, 27, 13, -27, 13, 17, 99, 103};
    vector b {"foo"s, "bar"s, "baz"s, "quux"s, "foobar"s};
    vector c {4.0+1.2i, -2.7+0.4i, 0.0+9.1i, 0.0-1.0i};
    vector<float> d;
}
