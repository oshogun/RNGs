#include "rng.hpp"
#include <iostream>

using namespace PRNG;

void Xorshift32::srand(unsigned int seed)
{
    state = seed;
}

unsigned int Xorshift32::xorshift32()
{
    if (state == 0)
        throw std::runtime_error("Xorshift seed cannot be 0");
    
    unsigned int x = state; 
    #ifdef _DEBUG
    cout << "\033[1;31m State before first xorshift: " << x << "\033[0m\n";
    #endif 

    x ^= x << 13;
    #ifdef _DEBUG
    cout << "\033[1;32m State before second xorshift: " << x << "\033[0m\n";
    #endif 

    x ^= x >> 17;

    #ifdef _DEBUG
    cout << "\033[1;33m State before third xorshift: " << x << "\033[0m\n";
    #endif 

    x ^= x << 5;

    #ifdef _DEBUG
    cout << "\033[1;34m State before function return: " << x << "\033[0m\n";
    #endif 

    return state = x;
}

unsigned int Xorshift32::random32()
{
    return xorshift32();
}

unsigned long long Xorshift32::random64()
{
    unsigned long long n = xorshift32();
    n |= static_cast<unsigned long long>(xorshift32()) << 32;
    return n;
}

cpp_int Xorshift32::random(unsigned int bits)
{
    if (bits == 0)
        throw std::runtime_error("Invalid number of bits");
    cpp_int bigNum;
    // avoid unnecessary overhead for 32 bit numbers
    if (bits == 32)
        return cpp_int(random32());
    
    // finds the closest multiple of 64 to n
    int n = bits / 64 == 0 ? 1 : bits / 64;
    for (int i = 0; i < n; i++) {
        bigNum |= cpp_int(random64()) << 64 * i;
    }

    // if the number of bits is not a multiple of 64,
    // truncate it
    if (bits % 64 != 0)
        bigNum = bigNum % pow(cpp_int(2), bits);
    return bigNum;
}