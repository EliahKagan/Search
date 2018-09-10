#ifndef POOLCLASS
#define POOLCLASS

#include <deque>

template <typename T>
class Pool
{
    public:
        T* newmem();
    private:
        std::deque<T> q;
};

template <typename T>
T* Pool<T>::newmem()
{
   return &(q.emplace_back());
}

#endif // ! POOLCLASS
