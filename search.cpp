#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include "Pool-test.h"
#include "Lnode.h"

namespace {
    class Foo {
    public:
        Foo() = default;
        Foo (const Foo &) = delete;
        Foo& operator = (const Foo &) = delete;
        Foo(Foo&&) = default;
        Foo& operator = (Foo &&) = default;
    };

    std::ostream& operator<<(std::ostream& out, const Foo&)
    {
        return out << "Foo!";
    }

    template <class T>
    void print(const std::vector<T>& vec)
    {
        auto sep = "";
        for (const auto& x : vec)
        {
            std::cout << sep << x;
            sep = " ";
        }
        std::cout << '\n';
    }

    bool mycompare(int i, int j)
    {
        if (i % 2 == 0 && j % 2 == 1)
            return false;
        else if (i % 2 == 1 && j % 2 == 0)
            return true;
        else
            return (i < j);
    }

    bool eliah_compare(const int lhs, const int rhs)
    {
        return lhs % 2 == rhs % 2 ? lhs < rhs     // same parity, just compare
                                  : lhs % 2 != 0; // check if the odd is first
    }

    void vector_sort(std::vector<int>& vec)
    {
        std::sort(begin(vec), end(vec), [] (const int lhs, const int rhs) {
            return lhs % 2 == rhs % 2
                               ? lhs < rhs
                               : lhs % 2 != 0;
        });
    }

    void vector_sort_alt(std::vector<int>& vec)
    {
        std::sort(vec.begin(), vec.end());
        std::stable_sort(vec.begin(), vec.end(), [] (const int i, const int j) {
            //return i % 2 > j % 2;
            return i % 2 == 1 && j % 2 == 0;
        });
    }

    template <class T>
    std::ptrdiff_t vindex(const std::vector<T>& vec, const T& el)
    {
        //return first occurance
        auto it = std::find(vec.begin(), vec.end(), el);
        //element is not it
        if (it != std::end(vec))
            return std::distance(vec.begin(),it);
        else
            return -1;
    }

    template<class T>
    std::ptrdiff_t vindex_alt(const std::vector<T>& vec, const T& el)
    {
        for (decltype(size(vec)) i {0}; i != size(vec); ++i) {
            if (vec[i] == el)
                return static_cast<std::ptrdiff_t>(i);
        }

        return -1;
    }
}

int main()
{
    std::vector<int> test {8, 1, 3, 7, 4, 5, 2, 9, 0, 6};
    //std::vector test2 {"hello","my","friend"};

    Pool <Lnode<int>> p;
    Lnode<int>* start = make_list(test, p);

    std::vector<int> test2 = make_vector(start);

    print(test2);
    vector_sort(test2);
    print(test2);

    Lnode<int>* three = search_list(start, 3);
    if (three != nullptr)
        std::cout << three->element << "is located at address" << three <<"\n";
    else
        std::cout << "No three found\n";




    //std::vector<Foo> test3(5);

    //std::cout << vindex(test, 2) << '\n';
    //std::cout << vindex_alt(test, 2) << '\n';
    //std::cout << vindex(test, 20) << '\n';
    //std::cout << vindex_alt(test, 20) << '\n';

    //test_pool();
}
