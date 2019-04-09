#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>

using std::cout;

static const unsigned int CYCLE = 4096;
static const unsigned int C_MAX = 809430660;

struct State {
    std::array<uint32_t, CYCLE> Q;
    uint32_t c;
    unsigned int i;
};

uint32_t rand32()
{
    uint32_t random = rand();
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

uint32_t randCMWC(State * state)
{
    uint64_t const a = 18782;
    uint32_t const m = 0xfffffffe;
    uint64_t t;
    uint32_t x;

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
int main(int argc, char **argv)
{
    if(argc != 2){
        cout << "Usage: " << argv[0] << " [SEED]";
        return 0;
    }
    
    State cmwc;
    unsigned int seed = static_cast<unsigned int>(atoi(argv[1]));
    initCMWC(&cmwc, seed);
    cout << randCMWC(&cmwc) << "\n";
    cout << randCMWC(&cmwc) << "\n";
    cout << randCMWC(&cmwc) << "\n";
    cout << randCMWC(&cmwc) << "\n";
}