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
    Lnode* head = nullptr;
    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        Lnode* temp = p.newmem();
        temp->element = *it;
        temp->next = head;
        head = temp;
    }
}

#endif // ! LNODESTRUCT
