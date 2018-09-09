#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

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
                                : lhs % 2 != 0;});
    }

    void vector_sort_alt(std::vector<int>& vec)
    {
       // https://en.cppreference.com/w/cpp/algorithm/stable_sort
       std::stable_sort(vec.begin(), vec.end());
       std::stable_sort(vec.begin(), vec.end(), [] (const int i, const int j) {
              if (i % 2 == 0 && j % 2 == 1)
                 return false;
            else if (i % 2 == 1 && j % 2 == 0)
                 return true;
                          } );

    }
}

int main()
{
    std::vector test {8, 1, 3, 7, 4, 5, 2, 9, 0, 6};
    std::vector test2 {"hello","my","friend"};
    std::vector<Foo> test3(5);
    print (test);
    print (test2);
    print (test3);
    vector_sort(test);
    print (test);
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
