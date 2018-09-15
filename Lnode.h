#ifndef LNODESTRUCT
#define LNODESTRUCT

#include "Pool.h"
#include <vector>

template <typename T>
struct Lnode
{
    T element;
    Lnode* next;
};

template <typename T>
Lnode<T>* make_list(const std::vector<T>& v, Pool<Lnode<T>>& p)
{
    for (auto i: v)
    {

    }
}

#endif // ! LNODESTRUCT
