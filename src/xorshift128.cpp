#include "rng.hpp"

using namespace PRNG;

void Xorshift128::srand(std::array<unsigned int, 4> seed)
{
    if(seed[0] == 0 && seed[1] == 0 && seed[2] == 0 && seed[3] == 0)
        throw std::runtime_error("Seed can't be all zeroes");
    
    state = seed;
}

unsigned int Xorshift128::xorshift128()
{
    unsigned int s, t = state[3];
    state[3] = state[2];
    state[2] = state[1];
    state[1] = s = state[0];
    t ^= t << 11;
    t ^= t >> 8;
    return state[0] = t ^ s ^ (s >> 19);
}

unsigned int Xorshift128::random32()
{
    return xorshift128();
}

unsigned long long Xorshift128::random64()
{
    unsigned long long n = xorshift128();
    n |= static_cast<unsigned long long>(xorshift128()) << 32;
    return n;
}

cpp_int Xorshift128::random(unsigned int bits)
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