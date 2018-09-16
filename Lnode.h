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
std::vector<T> make_vector(const Lnode<T>* list)
{
    vector<T> rvec;

    while (list != nullptr) //If list doesn't end, BAD!!!!!!
    {
        rvec.push_back(list->element);
        list = list->next;
    }
}

#endif // ! LNODESTRUCT
