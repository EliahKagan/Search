#include <iostream>
#include <vector>

template <class T>
void vector_print(vector<T> vec)
{
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
}


int main()
{
    std::cout << "...your feelings. You know it to be true!\n"; // searching it is!
}
