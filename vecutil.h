#ifndef VECUTIL
#define VECUTIL

#include <iostream>
#include <vector>

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

#endif // !VECUTIL
