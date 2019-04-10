#include "rng.h"
#include <iostream>

int main()
{
    PRNG::Xorshift32 xorzao;
    xorzao.srand(1234567);
    PRNG::Xorshift64 xorzao64;
    xorzao64.srand(5678910);
    std::cout << xorzao.random32() << "\n";
    std::cout << xorzao.random64() << "\n";
    std::cout << xorzao.random(16) << "\n";
    std::cout << xorzao.random(3200) << "\n";
    std::cout << xorzao64.random32() << "\n";
    std::cout << xorzao64.random64() << "\n";
    std::cout << xorzao64.random(16) << "\n";
    std::cout << xorzao64.random(3200) << "\n";
}