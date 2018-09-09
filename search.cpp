#include <iostream>
#include <vector>

template <class T>
void vector_print(const std::vector<T> &vec)
{
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}


int main()
{
    std::vector test {1,2,3};
    vector_print (test);
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
