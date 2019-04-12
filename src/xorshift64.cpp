#include "rng.hpp"

using namespace PRNG;

void Xorshift64::srand(unsigned long long seed)
{
    state = seed;
}

unsigned long long Xorshift64::xorshift64()
{
    if (state == 0) 
        throw std::runtime_error("Invalid xorshift seed");   

    unsigned long long x = state;
    
    #ifdef _DEBUG
    cout << "\033[1;31m State before first xorshift: " << x << "\033[0m\n";
    #endif 
    x ^= x << 13;
    
    #ifdef _DEBUG
    cout << "\033[1;32m State before second xorshift: " << x << "\033[0m\n";
    #endif 
    x ^= x >> 7;

    #ifdef _DEBUG
    cout << "\033[1;33m State before third xorshift: " << x << "\033[0m\n";
    #endif 
    x ^= x << 17;
    return state = x;
}

cpp_int Xorshift64::xorshift4096_64()
{
    cpp_int n;
    for(int i = 0; i < 64; i++) {
        n |= cpp_int(xorshift64()) << 64 * i;
    }
    return n;
}

unsigned long long Xorshift64::random64()
{
    return xorshift64();
}

unsigned int Xorshift64::random32()
{
    return static_cast<unsigned int> (xorshift64() % 4294967296);
}

cpp_int Xorshift64::random(unsigned int bits)
{
    if (bits == 0)
        throw std::runtime_error("Invalid number of bits");

    cpp_int bigNum;
    // avoid unnecessary overhead for 32 bit numbers
    if (bits == 32)
        return cpp_int(random32());
    // avoid unnecessary overhead for 64 bit numbers
    if (bits == 64)
        return cpp_int(random64());

    int n = bits / 64 == 0 ? 1 : bits / 64;
    for (int i = 0; i < n; i++) {
        bigNum |= cpp_int(random64()) << 64 * i;
    }
    if (bits % 64 != 0)
        bigNum = bigNum % pow(cpp_int(2), bits);
    return bigNum;
}