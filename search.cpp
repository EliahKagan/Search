#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <utility>
#include <vector>
#include "Pool-test.h"
#include "Lnode.h"
#include "loops.h"
#include "tree-test.h"

namespace {
    void hr()
    {
        std::cout << "\n\n";
        for (auto i = 100; i != 0; --i) std::cout << '=';
        std::cout << "\n\n\n";
    }

    class Foo {
    public:
        Foo() = default;
        Foo (const Foo &) = delete;
        Foo& operator = (const Foo &) = delete;
        Foo(Foo&&) = default;
        Foo& operator = (Foo &&) = default;
    };

    std::ostream& operator<<(std::ostream& out, const Foo&)
    {
        return out << "Foo!";
    }

    template <class T>
    void print(const std::vector<T>& vec)
    {
        auto sep = "";
        for (const auto& x : vec)
        {
            std::cout << sep << x;
            sep = " ";
        }
        std::cout << '\n';
    }

    bool mycompare(int i, int j)
    {
        if (i % 2 == 0 && j % 2 == 1)
            return false;
        else if (i % 2 == 1 && j % 2 == 0)
            return true;
        else
            return (i < j);
    }

    bool eliah_compare(const int lhs, const int rhs)
    {
        return lhs % 2 == rhs % 2 ? lhs < rhs     // same parity, just compare
                                  : lhs % 2 != 0; // check if the odd is first
    }

    void vector_sort(std::vector<int>& vec)
    {
        std::sort(begin(vec), end(vec), [] (const int lhs, const int rhs) {
            return lhs % 2 == rhs % 2
                               ? lhs < rhs
                               : lhs % 2 != 0;
        });
    }

    void vector_sort_alt(std::vector<int>& vec)
    {
        std::sort(vec.begin(), vec.end());
        std::stable_sort(vec.begin(), vec.end(), [] (const int i, const int j) {
            //return i % 2 > j % 2;
            return i % 2 == 1 && j % 2 == 0;
        });
    }

    template <class T>
    std::ptrdiff_t vindex(const std::vector<T>& vec, const T& el)
    {
        //return first occurance
        auto it = std::find(vec.begin(), vec.end(), el);
        //element is not it
        if (it != std::end(vec))
            return std::distance(vec.begin(),it);
        else
            return -1;
    }

    template<class T>
    std::ptrdiff_t vindex_alt(const std::vector<T>& vec, const T& el)
    {
        for (decltype(size(vec)) i {0}; i != size(vec); ++i) {
            if (vec[i] == el)
                return static_cast<std::ptrdiff_t>(i);
        }

        return -1;
    }

    template <typename T>
    std::vector<T> unique(const std::vector<T>& invector)
    {
        std::unordered_set<T> s;
        std::vector<T> outvector;
        for (auto &i: invector)
        {
        //if the element isn't already in the set, copy to outvector
            if (s.find(i) == s.end())
                outvector.push_back(i);
            //insert into set
            s.insert(i);
        }
        return outvector;
    }

    void test_lists()
    {
        std::vector<int> test {8, 1, 3, 7, 4, 5, 2, 9, 0, 6};
        //std::vector test1 {"hello","my","friend"};

        Pool <Lnode<int>> p;
        Lnode<int>* start = make_list(test, p);
        Lnode<int>* copytest = make_list(test, p);
        assert(list_equal(start, copytest));
        print_list(start);
        std::cout << "print function output above\n";

        auto start2 = make_list_fwd(test, p);
        auto start3 = make_list_fwd_eliah(test, p);
        assert(list_equal(start2, start3));

        std::vector<int> test2 = make_vector(start);
        auto test2a = test2, test2b = test2, test2c = test2;

        print(test2);
        vector_sort(test2);
        vector_sort_alt(test2a);
        std::sort(begin(test2b), end(test2b), mycompare);
        std::sort(begin(test2c), end(test2c), eliah_compare);

        for (const auto& testvec : {test2, test2a, test2b, test2c}) print(testvec);
        std::cout << '\n';

        std::vector<Foo> test3 (5);
        print(test3);

        std::cout << vindex(test, 2) << '\n';
        std::cout << vindex_alt(test, 2) << '\n';
        std::cout << vindex(test, 20) << '\n';
        std::cout << vindex_alt(test, 20) << '\n';

        test_pool();

        for (const auto value : {3, 10}) {
            const auto node = search_list(start, value);
            assert(node == search_list_eliah(start, value));

            if (node) {
                std::cout << node->element << " found at "
                        << static_cast<const void*>(node) << ".\n";
            } else {
                std::cout << value << " not found.\n";
            }
        }

        std::cout << "modified original, and unmodified copy, below\n";
        auto start_copy = copy_list(start, p);
        std::cout << list_equal(start, start_copy) << ' '
                << list_equal(start, start_copy) << '\n';
        //start->next->next->element *= 1000;
        start->next->next->next->next = nullptr;
        print_list(start);
        print_list(start_copy);
        std::cout << list_equal(start, start_copy) << ' '
                << list_equal(start, start_copy) << '\n';

        start = reverse_list(start);
        print_list(start);

        std::cout << '\n';
        auto start_copy2 = copy_list(start_copy, p);
        auto splitpair = split_list(start_copy, [](auto x) { return x > 5; });
        print_list(splitpair.first);
        print_list(splitpair.second);
        auto splitpair2 = split_list_eliah(start_copy2, [](auto x) { return x > 5; });
        print_list(splitpair2.first);
        print_list(splitpair2.second);

        auto sorted = make_list(std::vector{
                        1, 2, 7, 9, 14, 15, 19, 20, 22, 31, 36, 44, 57, 61}, p);
        auto sorted1 = copy_list(sorted, p);
        constexpr auto is_even = [](auto x) { return x % 2 == 0; };

        std::cout << '\n';
        print_list(sorted);
        auto [evens, odds] = split_list(sorted, is_even);
        print_list(evens);
        print_list(odds);
        sorted = merge_lists(odds, evens);
        print_list(sorted);

        std::cout << '\n';
        print_list(sorted1);
        auto [evens1, odds1] = split_list_eliah(sorted1, is_even);
        print_list(evens1);
        print_list(odds1);
        sorted1 = merge_lists(odds1, evens1);
        print_list(sorted1);

        std::cout << '\n';
        constexpr Lnode<int>* empty {};
        print_list(merge_lists(empty, sorted));
        print_list(merge_lists(sorted, empty));
        print_list(merge_lists_eliah(empty, sorted));
        print_list(merge_lists_eliah(sorted, empty));

        std::cout << '\n';
        auto sorted2 = make_list(std::vector{10, 15, 15, 20, 22, 22, 22, 25, 30}, p);
        auto sorted3 = make_list(std::vector{5, 15, 20, 22, 25}, p);
        std::cout << list_equal(merge_lists(copy_list(sorted2, p),
                                            copy_list(sorted3, p)),
                                merge_lists_eliah(copy_list(sorted2, p),
                                                copy_list(sorted3, p))) << ' '
                << list_equal_eliah(merge_lists(copy_list(sorted2, p),
                                                copy_list(sorted3, p)),
                                    merge_lists_eliah(copy_list(sorted2, p),
                                                        copy_list(sorted3, p))) << '\n';

        print_list(merge_lists(copy_list(sorted2, p), copy_list(sorted3, p)));
        print_list(merge_lists(sorted3, sorted2));

        std::cout << '\n';
        auto cyclic = make_list(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, p);
        std::cout << has_cycle(cyclic) << '\n';
        auto head = cyclic;
        while (head->next) head = head->next; // go to the last node
        head->next = cyclic->next->next->next;
        std::cout << has_cycle(cyclic) << '\n';

        std::cout << '\n';
        auto cyclic2 = make_list(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, p);
        std::cout << has_cycle_floyd_alt(cyclic2) << '\n';
        auto head2 = cyclic2;
        while (head2->next) head2 = head2->next; // go to the last node
        head2->next = cyclic2->next->next->next;
        std::cout << has_cycle_floyd_alt(cyclic2) << '\n';

        std::cout << '\n';
        print(unique(std::vector{
                10, -7, 3, 2, 4, 10, 10, 10, 10, 10, 7, 10, 10, 99, 8, 2, 7, 3, 1}));

        std::cout << '\n';
        auto nmlist1 = make_list(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, p);
        auto nmlist2 = make_list(std::vector{3, 4, 5, 6, 7, 8, 9, 10}, p);
        std::cout << lists_meet(nmlist1, nmlist2) << ' ' << lists_meet(nmlist2, nmlist1) << '\n';
        auto mhead = nmlist1->next->next->next;
        mhead->next = nmlist2; //they should meet now
        std::cout << lists_meet(nmlist1, nmlist2) << ' ' << lists_meet(nmlist2, nmlist1) << '\n';
        std::cout << lists_meet(empty, nmlist1) << ' ' << lists_meet(nmlist1, empty) << '\n';

        std::cout << '\n';
        std::cout << list_size(nmlist2) << '\n'; // should be 8
        std::cout << list_size(sorted) << '\n'; // should be 14
        std::cout << list_size(empty) << '\n'; // should be 0
        std::cout << '\n';

        auto mlist1 = make_list(std::vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, p);
        auto mlist2 = make_list(std::vector{3, 4, 5, 6, 7, 8, 9, 10}, p);
        std::cout << lists_meet_o1(mlist1, mlist2) << ' ' << lists_meet_o1(mlist2, mlist1) << '\n';
        auto nhead = mlist1->next->next->next;
        nhead->next = mlist2; //they should meet now
        std::cout << lists_meet_o1(mlist1, mlist2) << ' ' << lists_meet_o1(mlist2, mlist1) << '\n';
        std::cout << lists_meet_o1(empty, mlist1) << ' ' << lists_meet_o1(mlist1, empty) << '\n';
    }
}

int main()
{
    std::cout << std::boolalpha;

    test_loops();
    hr();
    test_lists();
    hr();
    test_trees();
}
