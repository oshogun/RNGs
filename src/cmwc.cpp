#include "rng.hpp"

using namespace PRNG;

CMWC::CMWC()
{
    for (unsigned i = 0; i < CYCLE; i++)
        state.Q[i] = rd();
    
    do
        state.c = rd();
    while (state.c >= C_MAX);
    state.i = CYCLE - 1;
}

unsigned int CMWC::randCMWC()
{
    unsigned long long const a = 18782;
    unsigned int const m = 0xfffffffe;
    unsigned long long t;
    unsigned int x;

    state.i = (state.i + 1) & (CYCLE - 1);
    t = a * state.Q[state.i] + state.c;

    state.c = t >> 32;
    x = t + state.c;
    if (x < state.c) {
        x++;
        state.c++;
    }
    return state.Q[state.i] = m - x;
}

cpp_int CMWC::randCMWC4096()
{
    cpp_int n;
    for(int i = 0; i < 128; i++) {
        n |= cpp_int(randCMWC()) << 32 * i;
    }
    return n;
}

unsigned int CMWC::random32()
{
    return randCMWC();
}

unsigned long long CMWC::random64()
{
    unsigned long long ull = randCMWC();
    ull |= static_cast<unsigned long long>(randCMWC()) << 32;
    return ull;
}

cpp_int CMWC::random(unsigned int bits)
{

    if (bits == 0)
        throw std::runtime_error("Invalid number of bits");
    
    cpp_int bigNum;
    // avoid unnecessary overhead for 32 bit numbers
    if (bits == 32)
        return cpp_int(random32());
        
    int n = bits / 64 == 0 ? 1 : bits / 64;
    
    for (int i = 0; i < n; i++) {
        bigNum |= cpp_int(random64()) << 64 * i;
    }
    if (bits % 64 != 0)
        bigNum = bigNum % pow(cpp_int(2), bits);
    return bigNum;
       
}
       
    
    
