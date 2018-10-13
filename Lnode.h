#ifndef LNODESTRUCT
#define LNODESTRUCT

#include "Pool.h"
#include <iostream>
#include <utility>
#include <vector>

template <typename T>
struct Lnode
{
    T element;
    Lnode* next;
};

template <typename T>
void print_list(const Lnode<T>* list)
{
    while (list != nullptr)
    {
        std::cout << list->element << ' ';
        list = list->next;
    }
    std::cout << '\n';
}

template <typename T>
Lnode<T>* copy_list(const Lnode<T>* list, Pool<Lnode<T>>& p)
{
    Lnode<T> sentinel {};
    auto cur = &sentinel;

    while (list != nullptr)
    {
        cur->next = p.newmem();
        cur = cur->next;
        cur->element = list->element;
        list = list->next;
    }

    return sentinel.next;
}

template <typename T>
Lnode<T>* make_list(const std::vector<T>& v, Pool<Lnode<T>>& p)
{
    Lnode<T>* head = nullptr;
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        Lnode<T>* temp = p.newmem();
        temp->element = *it;
        temp->next = head;
        head = temp;
    }
    return head;
}

template <typename T>
Lnode<T>* reverse_list(Lnode<T>* list)
{
    Lnode<T>* head = nullptr;
    while (list != nullptr)
    {
        Lnode<T>* temp = list->next;
        list->next = head;
        head = list;
        list = temp;
    }
    return head;
}


template <typename T>
Lnode<T>* make_list_fwd(const std::vector<T>& v, Pool<Lnode<T>>& p)
{
    Lnode<T>* head = nullptr;
    Lnode<T>* current = nullptr;

    for (auto& i: v)
    {
        if (head == nullptr)
        {
            //first element
            current = p.newmem();
            head = current;
            current->element = i;
        }
        else
        {
            //subsequent elements
            current->next = p.newmem();
            current = current->next;
            current->element = i;
        }
    }
    return head;
}

template <typename T>
Lnode<T>* make_list_fwd_eliah(const std::vector<T>& v, Pool<Lnode<T>>& p)
{
    Lnode<T> sentinel {};
    auto cur = &sentinel;

    for (const auto& x : v) {
        cur->next = p.newmem();
        cur = cur->next;
        cur->element = x;
    }

    return sentinel.next;
}

template <typename T>
std::vector<T> make_vector(const Lnode<T>* list)
{
    std::vector<T> rvec;

    while (list != nullptr) //If list doesn't end, BAD!!!!!!
    {
        rvec.push_back(list->element);
        list = list->next;
    }
    return rvec;
}

template <typename T>
Lnode<T>* search_list(Lnode<T>* list, const T& value)
{
    for (; list != nullptr; list = list ->next)
      if (list->element == value)
            break;

    return list;
}

template<typename T>
Lnode<T>* search_list_eliah(Lnode<T>* list, const T& value)
{
    while (list && list->element != value) list = list->next;
    return list;
}

template <typename T>
bool list_equal(Lnode<T>* list1, Lnode<T>* list2)
{
    while(list1 != nullptr && list2 != nullptr)
    {
        if (list1 -> element != list2 -> element)
            return false;

        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == nullptr && list2 == nullptr;
}

template <typename T>
bool list_equal_eliah(Lnode<T>* list1, Lnode<T>* list2)
{
    for (; list1 != list2; list1 = list1->next, list2 = list2->next) {
        if (!list1 || !list2 || list1->element != list2->element)
            return false;
    }

    return true;
}

// Returns (satisfy predicate, don't satisfy predicate).
template <typename T, typename F>
std::pair<Lnode<T>*, Lnode<T>*> split_list(Lnode<T>* list, F f)
{
    Lnode<T> fail_sentinel {0, list};
    auto pos = &fail_sentinel;

    Lnode<T> pass_sentinel {};
    auto passpos = &passlistsentinel;

    while (pos->next != nullptr)
    {
        if(f(pos->next->element))
        {
            passpos->next = pos->next;
            passpos = passpos->next;
            pos->next = pos->next->next;
        }
        else
            pos = pos->next;
    }
    return (make_pair(pass_sentinel.next, fail_sentinel.next));
}


#endif // ! LNODESTRUCT
