#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <vector>

using std::cout;

unsigned int & xorshift32(unsigned int & state)
{
    if (state == 0) 
        throw std::runtime_error("Invalid xorshift seed");
    
    unsigned int x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return state = x;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " {SEED}\n"; 
        return -1;
    }

    unsigned seed = atoi(argv[1]);
    cout << xorshift32(seed) << "\n";
    cout << xorshift32(seed) << "\n";
    cout << xorshift32(seed) << "\n";
    cout << xorshift32(seed) << "\n";
    cout << xorshift32(seed) << "\n";

}