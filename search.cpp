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

    void vector_sort(std::vector<int>& vec)
    {
        std::sort(begin(vec), end(vec), std::greater<>{});
    }
}

int main()
{
    std::vector test {59898,6, -344, 123, 4, 3992, 3};
    std::vector test2 {"hello","my","friend"};
    std::vector<Foo> test3(5);
    print (test);
    print (test2);
    print (test3);
    vector_sort(test);
    print (test);
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
