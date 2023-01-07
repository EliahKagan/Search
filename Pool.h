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

#ifndef POOLCLASS
#define POOLCLASS

#include <deque>
#include <utility>

template<typename T>
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

template<typename T>
template<typename... Args>
T* Pool<T>::operator()(Args&&... args)
{
   return &(q.emplace_back(std::forward<Args>(args)...));
}

template<typename T>
template<typename... Args>
inline T* Pool<T>::newmem(Args&&... args)
{
   return (*this)(std::forward<Args>(args)...);
}

#endif // ! POOLCLASS
