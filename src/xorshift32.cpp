#include "rng.h"
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

cpp_int Xorshift32::xorshift4096_32()
{
    cpp_int n;
    for(int i = 0; i < 128; i++) {
        n |= static_cast<cpp_int>(xorshift32()) << 32 * i;
    }
    return n;
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
    
    if (bits == 32)
        return static_cast<cpp_int>(random32());
    
    if (bits == 64)
        return static_cast<cpp_int>(random64());
    
    if (bits == 4096)
        return xorshift4096_32();
    
    cpp_int bigNum = xorshift4096_32();

    bigNum = bigNum % pow(cpp_int(2), bits);
    return bigNum;
}