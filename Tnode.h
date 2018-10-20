#ifndef TNODESTRUCT
#define TNODESTRUCT

#include "Pool.h"

template <typename T>
struct Tnode
{
    T element;
    Tnode* left;
    Tnode* right;
};


#endif //!TNODESTRUCT
