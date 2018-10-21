#include "tree-test.h"

#include "Pool.h"
#include "Tnode.h"

void test_trees()
{
    Pool<Tnode<int>> f;
    f(3,f(4),f(5));
}
