#ifndef TNODESTRUCT
#define TNODESTRUCT

#include <cstddef>
#include <functional>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
#include "Pool.h"


template <typename T>
struct Tnode
{
    T element;
    Tnode* left;
    Tnode* right;

    Tnode(const T& p, Tnode* l, Tnode* r) : element(p), left{l}, right{r} { }
    explicit Tnode(const T& p) : Tnode{p, nullptr, nullptr} { }
    Tnode(T&& p, Tnode* l, Tnode* r) : element(std::move(p)), left{l}, right{r} { }
    explicit Tnode(T&& p) : Tnode{std::move(p), nullptr, nullptr} { }
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
std::vector<T> tree_to_vector_pre(const Tnode<T>* tree)
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

template <typename T>
std::vector<T> tree_to_vector_post(const Tnode<T>* tree)
{
    std::vector<T> v;

    const std::function<void(const Tnode<T>*)> f = [&f, &v](const Tnode<T>* t) {
        if (t == nullptr) return;

        f(t->left);
        f(t->right);
        v.push_back(t->element);
    };

    f(tree);
    return v;
}

template <typename T>
std::vector<T> tree_to_vector_in(const Tnode<T>* tree)
{
    std::vector<T> v;

    const std::function<void(const Tnode<T>*)> f = [&f, &v](const Tnode<T>* t) {
        if (t == nullptr) return;

        f(t->left);
        v.push_back(t->element);
        f(t->right);
    };

    f(tree);
    return v;
}

template <typename T>
void uglyprint(const Tnode<T>* tree, int indent = 0)
{
    if (tree == nullptr)
        return;

    uglyprint(tree->left, indent + 1);
    //do stuff
    uglyprint(tree->right, indent + 1);
}


template <typename T>
std::vector<T> tree_to_vector_level(const Tnode<T>* tree)
{
    std::vector<T> v;
    std::queue<const Tnode<T>*> q;

    if (tree != nullptr)
    {
        for (q.push(tree); !q.empty(); q.pop())
        {
            //enque children of current Node
            //if they are nonnull
            if (q.front()->left != nullptr)
                q.push(q.front()->left);
            if (q.front()->right != nullptr)
                q.push(q.front()->right);

            //use the current element
            v.push_back(q.front()->element);
        }
    }
    return v;
}

template <typename T>
std::vector<T> tree_to_vector_preit(const Tnode<T>* tree)
{
    std::vector<T> v;
    std::stack<const Tnode<T>*> s;

    if (tree != nullptr)
        s.push(tree);

    while (!s.empty())
    {
        //use the current element
        const Tnode<T>* temp = s.top();
        s.pop();
        v.push_back(temp->element);

        //enstack children of current Node
        //if they are nonnull
        if (temp->right != nullptr)
            s.push(temp->right);
        if (temp->left != nullptr)
            s.push(temp->left);
    }

    return v;
}

#endif //!TNODESTRUCT
