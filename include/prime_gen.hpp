#pragma once 

#include "rng.hpp"

namespace PRNG 
{
    class Prime_Generator {
        public:
            cpp_int generateOdd(PRNG & rng, unsigned int bits);
    };
}