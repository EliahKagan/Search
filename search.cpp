#include <iostream>
#include <iterator>
#include <vector>

template <class T>
void vector_print(const std::vector<T> &vec)
{
    if (empty(vec)) return;

    const auto last = cend(vec);
    auto first = cbegin(vec);

    std::cout << *first;

    while (++first != last) std::cout << *first << '\n';
}


int main()
{
    std::vector test {1,2,3};
    std::vector test2 {"hello","my","friend"};
    vector_print (test);
    vector_print (test2);
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
