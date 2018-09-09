#include <iostream>
#include <vector>

template <class T>
void vector_print(const std::vector<T> &vec)
{
    auto sep = "";
    for (const auto& x : vec) {
        std::cout << sep << x;
        sep = " ";
    }
}


int main()
{
    std::vector test {1,2,3};
    std::vector test2 {"hello","my","friend"};
    vector_print (test);
    vector_print (test2);
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
