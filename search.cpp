#include <iostream>
#include <iterator>
#include <vector>

namespace {
    class Foo {
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
}

template <class T>
void vector_print(const std::vector<T> &vec)
{
    auto sep = "";
    for (const auto& x : vec)
    {
        std::cout << sep << x;
        sep = " ";
    }
    std::cout << '\n';
}


int main()
{
    std::vector test {1,2,3};
    std::vector test2 {"hello","my","friend"};
    std::vector<Foo> test3(5);
    vector_print (test);
    vector_print (test2);
    vector_print (test3);
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
