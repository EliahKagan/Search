#include "Pool-test.h"

#include <iostream>
#include <iterator>
#include <mutex>
#include <numeric>
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
    T sum(const std::vector<T>& items) // test_general_construction helper
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
        std::cout << sum(*vp) << ' ' << sum(*vp3) << '\n';
    }
}

void test_pool()
{
    test_default_construction();
    std::cout << '\n';
    test_nonmovable_construction();
    test_general_construction();
}
