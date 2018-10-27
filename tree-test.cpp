#include "tree-test.h"

#include <iostream>
#include "Pool.h"
#include "Tnode.h"
#include "vecutil.h"

using namespace std;

void test_trees()
{
    constexpr const Tnode<int>* empty {};
    Pool<Tnode<int>> f;

    auto root = f(3, f(4), f(5));
    cout << tree_size(empty) << ' ' << tree_size(root) << '\n';

    vector<int> v = tree_to_vector_pre(root);
    print(v);

    auto root2 = f(9, root,
                      f(2, nullptr,
                           f(6)));
    print(tree_to_vector_pre(root2));
}
