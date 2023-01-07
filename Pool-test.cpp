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

#include "Pool-test.h"

#include <iostream>
#include <iterator>
#include <mutex>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include "Pool.h"

namespace {
    class Noisy;

    std::ostream& operator<<(std::ostream&, const Noisy&);

    class Noisy {
    public:
        Noisy() { std::cout << "Default constructed " << *this << '\n'; }

        Noisy(const Noisy&) { std::cout << "Copy constructed " << *this << '\n'; }

        Noisy(Noisy&&) { std::cout << "Move constructed " << *this << '\n'; }

        Noisy& operator=(const Noisy&)
        {
            std::cout << "Copy assigned to " << *this << '\n';
            return *this;
        }

        Noisy& operator=(Noisy&&)
        {
            std::cout << "Move assigned to " << *this << '\n';
            return *this;
        }

        ~Noisy() { std::cout << "Destroying " << *this << '\n'; }
    };

    std::ostream& operator<<(std::ostream& out, const Noisy& noisy)
    {
        return out << static_cast<const void*>(&noisy);
    }

    constexpr auto interactive = false;

    void test_default_construction()
    {
        Pool<Noisy> pool;
        for (auto i = 5; i != 0; --i) {
            auto& noisy = *pool.newmem();
            std::cout << '[' << noisy << "]\n";
        }

        if (interactive) {
            std::cout << "\nPress enter now... ";
            std::cin.get();
        }
        else std::cout << "Destroying pool...\n";
    }

    void test_nonmovable_construction()
    {
        Pool<std::mutex> mut_pool;
        auto mp = mut_pool();
        std::cout << "Constructed std::mutex at "
                  << static_cast<const void*>(mp) << '\n';
    }

    template<typename T>
    T sum(const std::vector<T>& items) // helper for test_general_construction
    {
        return std::accumulate(cbegin(items), cend(items), 0);
    }

    void test_general_construction()
    {
        Pool<std::vector<int>> pool;
        auto vp = pool(11, 3);
        const auto vp2 = pool(*vp);
        std::cout << sum(*vp) << ' ' << sum(*vp2) << ' ';
        auto vp3 = pool(std::move(*vp));
        std::cout << sum(*vp) << ' ' << sum(*vp3) << "\n\n";

        Pool<std::mt19937_64> epool;
        constexpr auto s = 31337;
        std::vector<std::mt19937_64*> eps {epool(s), epool(s)};
        eps.push_back(epool(*eps[0]));
        eps.push_back(epool(*eps[1]));
        for (auto i = 0; i != size(eps); ++i) eps[i]->discard(i);
        for (auto i = 8; i != 0; --i) {
            for (const auto ep : eps) std::cout << ' ' << (*ep)() % 1000;
            std::cout << '\n';
        }
    }
}

void test_pool()
{
    test_default_construction();
    std::cout << '\n';
    test_nonmovable_construction();
    test_general_construction();
}
