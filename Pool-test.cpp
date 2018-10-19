#include "Pool-test.h"
#include <iostream>
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
}

void test_pool()
{
    std::cout << '\n';

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

    std::cout << '\n';
}
