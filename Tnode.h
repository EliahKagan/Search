#ifndef TNODESTRUCT
#define TNODESTRUCT

#include <cstddef>
#include <utility>
#include "Pool.h"

template <typename T>
struct Tnode
{
    T element;
    Tnode* left;
    Tnode* right;

    Tnode(T p, Tnode* l, Tnode* r) : element{std::move(p)}, left{l}, right{r} { }
    explicit Tnode(T p) : element{std::move(p)}, left{}, right{} { }

};

template <typename T>
std::size_t tree_size(const Tnode<T>* tree)
{
    std::size_t count {};


}

#endif //!TNODESTRUCT
