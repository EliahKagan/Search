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

    void vector_sort(std::vector<int>& vec)
    {
        std::sort(begin(vec), end(vec), mycompare);
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
