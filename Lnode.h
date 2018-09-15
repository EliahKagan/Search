#ifndef LNODESTRUCT
#define LNODESTRUCT

#include "Pool.h"

template <typename T>
struct Lnode
{
    T element;
    Lnode* next;
};

template <typename T>
Lnode<T>* make_list(vector <T> v)
{

}

#endif // ! LNODESTRUCT
