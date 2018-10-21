#ifndef TNODESTRUCT
#define TNODESTRUCT

#include "Pool.h"

template <typename T>
struct Tnode
{
    T element;
    Tnode* left;
    Tnode* right;

    Tnode(T p, Tnode* l, Tnode* r)
    {
        element = p;
        *left = l;
        *right = r;
    }
};


#endif //!TNODESTRUCT
