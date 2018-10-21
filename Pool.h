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

class Foo { };

void g(const Foo&);
void g(Foo&&);

void f(const Foo& x)
{
    // do stuff with x

    g(x);
}

void f(Foo&& x)
{
    // do stuff with x

    g(std::move(x));
}

template<typename T>
void h(T&& x)
{
    // do stuff with x

    g(std::forward<T>(x));
}

template<typename T>
class Bar {
    void otherfunc(T&& x);
};

#endif // ! POOLCLASS
