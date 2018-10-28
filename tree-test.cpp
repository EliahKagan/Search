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

    print(tree_to_vector_pre(root));
    print(tree_to_vector_preit(root));
    print(tree_to_vector_preit_alt(root));
    print(tree_to_vector_in(root));
    print(tree_to_vector_post(root));
    print(tree_to_vector_level(root));

    auto root2 = f(9, root,
                      f(2, nullptr,
                           f(6)));
    print(tree_to_vector_pre(root2));
    print(tree_to_vector_preit(root2));
    print(tree_to_vector_preit_alt(root2));
    print(tree_to_vector_in(root2));
    print(tree_to_vector_post(root2));
    print(tree_to_vector_level(root2));

    cout <<"\n\n";
    uglyprint(root);
    cout << "\n\n";
    uglyprint(root2);

    auto root3 = root2;
    for (auto i = 10; i > 0; i -= 2) {
        root3 = f(i, root3, nullptr);
        root3 = f(i - 1, nullptr, root3);
    }
    cout << "\n\n";
    uglyprint(root3);

    cout << "\n\n";
    prettyprint(root);

    cout << "\n\n";
    prettyprint(root2);

    cout << "\n\n";
    prettyprint(root3);
}
