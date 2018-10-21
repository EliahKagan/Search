#ifndef POOLCLASS
#define POOLCLASS

#include <deque>

template <typename T>
class Pool
{
    public:
        template<typename... Args>
        T* newmem(Args&&... args);

    private:
        std::deque<T> q;
};

template <typename T>
template <typename... Args>
T* Pool<T>::newmem(Args&&... args)
{
   return &(q.emplace_back(std::forward<Args>(args)...));
}

#endif // ! POOLCLASS
