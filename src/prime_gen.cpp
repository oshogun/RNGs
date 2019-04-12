#include "prime_gen.hpp"

using namespace PRNG;

cpp_int Prime_Generator::generateOdd(PRNG & rng, unsigned int bits)
{
    cpp_int number;
    
    do {
        number = rng.random(bits);
    } while (number % 2 == 0);

    return number;
}