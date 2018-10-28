#ifndef TNODESTRUCT
#define TNODESTRUCT

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
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

    //print current element
    for(int x = indent; x > 0; x--)
        std::cout << "    ";
    std::cout << tree->element << '\n';

    uglyprint(tree->right, indent + 1);
}

namespace detail {
    template<typename T>
    struct ColNodePair {
        int col;
        const Tnode<T>* node;
    };

    template<typename T>
    std::vector<std::vector<ColNodePair<T>>>
    get_prettyprint_table(const Tnode<T>* const tree)
    {
        std::vector<std::vector<ColNodePair<T>>> table;

        auto put = [&table, j = 0](const Tnode<T>* const node,
                                   const int i) mutable {
            if (size(table) <= i) table.resize(i + 1);
            table.at(i).push_back({j++, node});
        };

        const std::function<void(const Tnode<T>*, int)>
        dfs = [&put, &dfs](const Tnode<T>* const node, const int depth) {
            if (!node) return;

            dfs(node->left, depth + 1);
            put(node, depth);
            dfs(node->right, depth + 1);
        };

        dfs(tree, 0);
        return table;
    }
}

template<typename T>
void prettyprint(const Tnode<T>* tree)
{
    static constexpr auto item_width = 3, padding = 2;
    static constexpr auto field_width = item_width + padding;

    for (const auto& row : detail::get_prettyprint_table(tree)) {
        auto cursor_col = 0;

        for (const auto [col, node] : row) {
            const auto delta = col - cursor_col;
            assert(delta >= 0);

            std::cout << std::setw(field_width * delta + padding) << ""
                      << std::setw(item_width) << node->element;

            cursor_col = col;
        }

        std::cout << '\n';
    }
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
