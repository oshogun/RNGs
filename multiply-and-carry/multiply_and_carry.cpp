#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

using std::cout;
using namespace boost::multiprecision;

static const unsigned int CYCLE = 4096;
static const unsigned int C_MAX = 809430660;

struct State {
    std::array<unsigned int, CYCLE> Q;
    unsigned int c;
    unsigned int i;
};

unsigned int rand32()
{
    unsigned int random = rand();
    return random << 16 | rand();
}

void initCMWC(State * state, unsigned int seed)
{
    srand(seed);
    for (unsigned i = 0; i < CYCLE; i++)
        state->Q[i] = rand32();
    
    do
        state->c = rand32();
    while (state->c >= C_MAX);
    state->i = CYCLE - 1;
}

unsigned int randCMWC(State * state)
{
    unsigned long long const a = 18782;
    unsigned int const m = 0xfffffffe;
    unsigned long long t;
    unsigned int x;

    state->i = (state->i + 1) & (CYCLE - 1);
    t = a * state->Q[state->i] + state->c;

    state->c = t >> 32;
    x = t + state->c;
    if (x < state->c) {
        x++;
        state->c++;
    }
    return state->Q[state->i] = m - x;
}

cpp_int randCMWC4096(State * state)
{
    cpp_int n;
    for(int i = 0; i < 128; i++) {
        n |= static_cast<cpp_int>(randCMWC(state)) << 32 * i;
    }
    return n;
}
int main(int argc, char **argv)
{
    if(argc != 2){
        cout << "Usage: " << argv[0] << " [SEED]";
        return 0;
    }
    
    State cmwc;
    unsigned int seed = static_cast<unsigned int>(atoi(argv[1]));
    initCMWC(&cmwc, seed);
    cout << randCMWC4096(&cmwc) << "\n";
}