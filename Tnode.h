#ifndef TNODESTRUCT
#define TNODESTRUCT

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>
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
    if (tree == nullptr)
        return 0;
    else
        return 1 + tree_size(tree->left) + tree_size(tree->right);
}

template <typename T>
std::vector<T> tree_to_vector(const Tnode<T>* tree)
{
    std::vector<T> v;

    const std::function<void(const Tnode<T>*)> f = [&f, &v](const Tnode<T>* t) {
        if (t == nullptr) return;

        v.push_back(t->element);
        f(t->left);
        f(t->right);
    };

    f(tree);
    return v;
}


#endif //!TNODESTRUCT
