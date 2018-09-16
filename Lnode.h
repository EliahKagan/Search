#ifndef LNODESTRUCT
#define LNODESTRUCT

#include "Pool.h"
#include <vector>

template <typename T>
struct Lnode
{
    T element;
    Lnode* next;
};

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
Lnode<T>* make_list_fwd(const std::vector<T>& v, Pool<Lnode<T>>& p)
{
    Lnode<T>* head = nullptr;
    Lnode<T>* current = nullptr;
    Lnode<T>* tail = nullptr;
    for (auto i: v)
    {

    }
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

#endif // ! LNODESTRUCT
