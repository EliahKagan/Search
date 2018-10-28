#include "tree-test.h"

#include <iostream>
#include <string_view>
#include "Pool.h"
#include "Tnode.h"
#include "vecutil.h"

namespace {
    using namespace std;

    void heading(const std::string_view text)
    {
        std::cout << "\n ::: " << text << " :::\n";
    }

    template<typename T>
    void do_traversals(const Tnode<T>* const root,
                       const std::string_view label = "-")
    {
        cout << label << "\n\n";

        cout << "Size " << tree_size(root) << '\n';

        const auto put = [](const auto& x) { std::cout << x << ' '; };

        heading("Preorder traversals");
        preorder(root, put);
        std::cout << '\n';
        print(tree_to_vector_pre(root));
        print(tree_to_vector_preit(root));
        print(tree_to_vector_preit_alt(root));

        heading("Inorder traversals");
        inorder(root, put);
        std::cout << '\n';
        print(tree_to_vector_in(root));

        heading("Postorder traversals");
        postorder(root, put);
        std::cout << '\n';
        print(tree_to_vector_post(root));

        heading("Level-order traversals");
        print(tree_to_vector_level(root));

        heading("\"Ugly\" print");
        uglyprint(root);

        heading("\"Pretty\" print");
        prettyprint(root);
        cout << "\n\n";
    }
}

void test_trees()
{
    Pool<Tnode<int>> f;

    constexpr const Tnode<int>* empty {};
    do_traversals(empty, "EMPTY TREE");

    const auto root1 = f(3, f(4), f(5));
    do_traversals(root1, "COMPLETE THREE-NODE TREE");

    auto root2 = f(9, root1,
                      f(2, nullptr,
                           f(6)));
    do_traversals(root2, "SLIGHTLY MORE COMPLEX TREE");

    auto root3 = root2;
    for (auto i = 10; i > 0; i -= 2) {
        root3 = f(i, root3, nullptr);
        root3 = f(i - 1, nullptr, root3);
    }
    do_traversals(root3, "(SOMEWHAT) LARGER AND QUITE UNBALANCED TREE");
}
