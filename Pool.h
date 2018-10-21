#ifndef POOLCLASS
#define POOLCLASS

#include <deque>
#include <utility>

template <typename T>
class Pool
{
    public:
        template<typename... Args>
        T* operator()(Args&&... args);

        template<typename... Args>
        T* newmem(Args&&... args); // for backward compatibility

    private:
        std::deque<T> q;
};

template <typename T>
template <typename... Args>
T* Pool<T>::operator()(Args&&... args)
{
   return &(q.emplace_back(std::forward<Args>(args)...));
}

template <typename T>
template <typename... Args>
inline T* Pool<T>::newmem(Args&&... args)
{
   return (*this)(std::forward<Args>(args)...);
}

#endif // ! POOLCLASS
