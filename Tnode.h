#ifndef TNODESTRUCT
#define TNODESTRUCT

#include "Pool.h"
#include <utility>

template <typename T>
struct Tnode
{
    T element;
    Tnode* left;
    Tnode* right;

    Tnode(T p, Tnode* l, Tnode* r) : element{std::move(p)}, left{l}, right{r} {}
    Tnode(T p) : element{std::move(p)}, left{}, right{} {}

};

#endif //!TNODESTRUCT
