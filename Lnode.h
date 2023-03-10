// Copyright (c) 2018 David Vassallo and Eliah Kagan
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef LNODESTRUCT
#define LNODESTRUCT

#include "Pool.h"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

template<typename T>
struct Lnode
{
    T element;
    Lnode* next;
};

template<typename T>
std::size_t list_size(const Lnode<T>* list)
{
    std::size_t count {};
    for (; list != nullptr; list = list ->next)
        ++count;
    return count;
}

template<typename T>
const Lnode<T>* advance_list_by(const Lnode<T>* list, std::size_t num)
{
    for (int i = 0; i < num; ++i) list = list->next;
    return list;
}

template<typename T>
void print_list(const Lnode<T>* list)
{
    while (list != nullptr)
    {
        std::cout << list->element << ' ';
        list = list->next;
    }
    std::cout << '\n';
}

template<typename T>
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

template<typename T>
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

template<typename T>
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


template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
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

template<typename T>
bool list_equal_eliah(Lnode<T>* list1, Lnode<T>* list2)
{
    for (; list1 != list2; list1 = list1->next, list2 = list2->next) {
        if (!list1 || !list2 || list1->element != list2->element)
            return false;
    }

    return true;
}

// Returns (satisfy predicate, don't satisfy predicate).
template<typename T, typename F>
std::pair<Lnode<T>*, Lnode<T>*> split_list(Lnode<T>* list, F f)
{
    Lnode<T> fail_sentinel {0, list};
    auto pos = &fail_sentinel;

    Lnode<T> pass_sentinel {};
    auto passpos = &pass_sentinel;

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

    passpos->next = nullptr;
    assert(pos->next == nullptr);

    return std::make_pair(pass_sentinel.next, fail_sentinel.next);
}

// Returns (satisfy predicate, don't satisfy predicate).
template<typename T, typename F>
std::pair<Lnode<T>*, Lnode<T>*> split_list_eliah(Lnode<T>* list, F f)
{
    Lnode<T> true_sentinel {}, false_sentinel {};
    auto true_pos = &true_sentinel, false_pos = &false_sentinel;

    for (; list; list = list->next) {
        if (f(list->element)) {
            true_pos->next = list;
            true_pos = true_pos->next;
        } else {
            false_pos->next = list;
            false_pos = false_pos->next;
        }
    }

    true_pos->next = false_pos->next = nullptr;
    return {true_sentinel.next, false_sentinel.next};
}

template<typename T>
Lnode<T>* merge_lists(Lnode<T>* top, Lnode<T>* bottom)
{
    Lnode<T> top_sentinel {0, top};
    auto tpos = &top_sentinel;

    Lnode<T> bottom_sentinel {0, bottom};
    auto bpos = &bottom_sentinel;

    while (tpos->next != nullptr && bpos->next != nullptr)
    {
        if(bpos->next->element < tpos->next->element)
        {
            auto bnext = bpos->next->next;
            bpos->next->next = tpos->next;
            tpos->next = bpos->next;
            bpos->next = bnext;
        }
        else
            tpos = tpos -> next;
    }
    if (tpos->next == nullptr)
        tpos->next = bpos->next;
    return top_sentinel.next;
}

template<typename T>
Lnode<T>* merge_lists_eliah(Lnode<T>* head1, Lnode<T>* head2)
{
    Lnode<T> sentinel {};
    auto pos = &sentinel;

    for (; head1 && head2; pos = pos->next) {
        if (head2->element < head1->element) {
            pos->next = head2;
            head2 = head2->next;
        } else {
            pos->next = head1;
            head1 = head1->next;
        }
    }

    pos->next = (head1 ? head1 : head2);
    return sentinel.next;
}

template<typename T>
bool has_cycle(const Lnode<T>* list)
{
    std::unordered_set<const Lnode<T>*> s;
    for(; list != nullptr; list = list->next)
    {
        if (s.find(list) != s.end())
            return true;
        s.insert(list);
    }
    return false;
}

template<typename T>
bool has_cycle_floyd(const Lnode<T>* list)
{
    const Lnode<T>* slow = list;
    const Lnode<T>* fast = list;

    for(; fast != nullptr && (fast = fast->next) != nullptr; slow = slow->next, fast = fast->next->next)
    {
        if (slow == fast)
            return true;
        if(fast->next == nullptr)
            return false;
    }
    return false;
}

template<typename T>
bool has_cycle_floyd_eliah(const Lnode<T>* list)
{
    for (auto fast = list; fast && (fast = fast->next); fast = fast->next) {
        if (list == fast) return true;
        if (!fast) return false;
        list = list->next;
    }

    return false;
}

template<typename T>
bool has_cycle_floyd_alt(const Lnode<T>* list)
{
    auto fast = list;

    while (fast && fast->next) {
        fast = fast->next->next;
        list = list->next;
        if (fast == list) return true;
    }

    return false;
}

// Checks if two lists share any nodes. Assumes they have no cycles.
template<typename T>
bool lists_meet(const Lnode<T>* lista, const Lnode<T>* listb)
{
    std::unordered_set<const Lnode<T>*> s;
    for(; lista != nullptr; lista = lista->next)
        s.insert(lista);
    for (; listb != nullptr; listb = listb->next)
          if (s.find(listb) != s.end())
            return true;
    return false;
}

template<typename T>
bool lists_meet_o1(const Lnode<T>* lista, const Lnode<T>* listb)
{
    auto asize = list_size(lista);
    auto bsize = list_size(listb);

    if (asize < bsize)
        listb = advance_list_by(listb, bsize - asize);
    else
        lista = advance_list_by(lista, asize - bsize);

    for(; lista != nullptr && listb != nullptr; lista = lista->next, listb = listb->next)
        if (lista == listb)
            return true;
    return false;
}

#endif // ! LNODESTRUCT
