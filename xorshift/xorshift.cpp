#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdint>

using std::cout;
using std::cin;

static uint32_t state32; // for xorshift32
static uint64_t state64; // for xorshift 64
static uint32_t state128[4]; // for xorshift 128

static uint32_t xorshift32()
{
    if (state32 == 0) 
        throw std::runtime_error("Invalid xorshift seed");
    
    uint32_t x = state32;

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

static uint32_t xorshift128()
{
    if (state128[0] == 0 && state128[1] == 0
        && state128[2] == 0 && state128[3] == 0) 
            throw std::runtime_error("Invalid xorshift seed");

    uint32_t s, t = state128[3];
    state128[3] = state128[2];
    state128[2] = state128[1];
    state128[1] = s = state128[0];
    t ^= t << 11;
    t ^= t >> 8;
    return state128[0] = t ^ s ^ (s >> 19);
}
int main(int argc, char **argv)
{
    cout << "Xorshift algorithm test\n";
    int choice = 0;
    while(!(choice > 0 && choice <= 3)) {
        cout << "Select algorithm: \n";
        cout << "1 - xorshift32\n";
        cout << "2 - xorshift64\n";
        cout << "3 - xorshift128\n";
        cin >> choice;
    }
    
    switch (choice) {
        case 1:
            cout << "Input seed:\n";
            cin >> state32;
            cout << "Generating a few numbers with xorshift32\n";
            cout << xorshift32() << "\n";
            cout << xorshift32() << "\n";
            cout << xorshift32() << "\n";
            break;
        case 2:
            cout << "Input seed:\n";
            cin >> state64;
            cout << "Generating a few numbers with xorshift64\n";
            cout << xorshift64() << "\n";
            cout << xorshift64() << "\n";
            cout << xorshift64() << "\n";
            break;
        default:
            cout << "Input first word of seed\n";
            cin >> state128[0];
            cout << "Input second word of seed\n";
            cin >> state128[1];
            cout << "Input third word of seed\n";
            cin >> state128[2];
            cout << "Input fourth word of seed\n";
            cin >> state128[3];
            

            cout << "Generating a few numbers with xorshift128\n";
            cout << xorshift128() << "\n";
            cout << xorshift128() << "\n";
            cout << xorshift128() << "\n";
            cout << xorshift128() << "\n";
    }

  


}