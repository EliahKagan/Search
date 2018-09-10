#include "Pool-test.h"
#include <iostream>

namespace {
    class Noisy;

    std::ostream& operator<<(std::ostream&, const Noisy&);

    class Noisy {
    public:
        Noisy() { std::cout << "Constructed " << *this << '\n'; }
    };
}

void test_pool()
{

}
