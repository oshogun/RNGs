#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

using std::cout;
using std::cin;
using namespace boost::multiprecision;

static unsigned int state32; // for xorshift32
static uint64_t state64; // for xorshift 64
static unsigned int state128[4]; // for xorshift 128

static unsigned int xorshift32()
{
    if (state32 == 0) 
        throw std::runtime_error("Invalid xorshift seed");
    
    unsigned int x = state32;

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

    return state32 = x;
}

static uint64_t xorshift64()
{
    if (state64 == 0) 
        throw std::runtime_error("Invalid xorshift seed");   

    uint64_t x = state64;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return state64 = x;
}

static unsigned int xorshift128()
{
    if (state128[0] == 0 && state128[1] == 0
        && state128[2] == 0 && state128[3] == 0) 
            throw std::runtime_error("Invalid xorshift seed");

    unsigned int s, t = state128[3];
    state128[3] = state128[2];
    state128[2] = state128[1];
    state128[1] = s = state128[0];
    t ^= t << 11;
    t ^= t >> 8;
    return state128[0] = t ^ s ^ (s >> 19);
}
int main(int argc, char **argv)
{
    if (argc < 3) {
        cout << "Usage " << argv[0] << "[32/64/128] [SEED] where ";
        cout << "[SEED] is the 1 to 4 words to seed the rng separated by ";
        cout << "spaces.\n";
        return 0;
    }
    int choice = atoi(argv[1]);
    int1024_t number;


    switch (choice) {
        case 32:
            state32 = static_cast<unsigned int>(atoi(argv[2]));

            #ifdef _DEBUG
            cout << "\033[1;34m xorshift32 with seed " << state32 << "\033[0m\n";
            #endif 

            // Generate a big boy
            for(int i = 0; i < 32; i++) {
                number |= static_cast<int1024_t>(xorshift32()) << 32 * i;
            }
            cout << number << "\n";
            break;
        case 64:
            state64 = static_cast<uint64_t> (atol(argv[2]));

            #ifdef _DEBUG
            cout << "\033[1;34m xorshift64 with seed " << state64 << "\033[0m\n";
            #endif 
            // Generate a big boy
            for(int i = 0; i < 16; i++) {
                number |= static_cast<int1024_t>(xorshift64()) << 64 * i;
            }
            cout << number << "\n";
            break;
        case 128:
            state128[0] = static_cast<unsigned int>(atoi(argv[2]));
            state128[1] = static_cast<unsigned int>(atoi(argv[3]));
            state128[2] = static_cast<unsigned int>(atoi(argv[4]));
            state128[3] = static_cast<unsigned int>(atoi(argv[5]));

            #ifdef _DEBUG
            cout << "\033[1;34m xorshift32 with seed {";
            cout << state128[0] << " " << state128[1];
            cout << " " << state128[2] << " " << state128[3];  
            cout << "}\033[0m\n";
            #endif 
            for(int i = 0; i < 32; i++) {
                number |= static_cast<int1024_t>(xorshift128()) << 32 * i;
            }
            
            
            cout << number << "\n";
            break;

        default:
            cout << "Invalid algorithm\n";
    }

  


}