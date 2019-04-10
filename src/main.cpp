#include "rng.h"
#include <iostream>
#include <cstdlib>

int main()
{
    PRNG::CMWC rng;


    std::cout << rng.random32() << "\n";
    std::cout << rng.random64() << "\n";
    std::cout << rng.random(16) << "\n";
    std::cout << rng.random(3200) << "\n";
    
}