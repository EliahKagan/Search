#include "tree-test.h"

#include <iostream>
#include "Pool.h"
#include "Tnode.h"

using namespace std;

void test_trees()
{
    Pool<Tnode<int>> f;
    auto root = f(3,f(4),f(5));
    cout << tree_size(root) << '\n';
}
