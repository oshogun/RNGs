#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <array>
#include <vector>
#include <stdexcept>
#include <iterator>

using boost::multiprecision::pow;
using boost::multiprecision::cpp_int;

namespace PRNG
{
    class PRNG {
        public:
            // Generates a pseudorandom unsigned bigint with a
            // given number of bytes 
            virtual cpp_int random(unsigned int bits) = 0;

            // Generates a 32 bit unsigned pseudorandom int
            virtual unsigned int random32() = 0;

            // Generates a 64 bit unsigned pseudorandom int
            virtual unsigned long long random64() = 0;
    };

    class Xorshift32: public PRNG {
        public:
            void srand(unsigned int seed);
            cpp_int random(unsigned int bits);
            unsigned int random32();
            unsigned long long random64();
            
        private:
            unsigned int state;
            unsigned int xorshift32();
            cpp_int xorshift4096_32();
    };

    class Xorshift64: public PRNG {
        public:
            void srand(unsigned long long seed);
            cpp_int random(unsigned int bits);
            unsigned int random32();
            unsigned long long random64();
            
        private:
            unsigned long long state;
            unsigned long long xorshift64();
            cpp_int xorshift4096_64();
    };
}


