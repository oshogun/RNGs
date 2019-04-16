#include "prime_gen.hpp"
#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

int main()
{
    PRNG::Xorshift32 rng;
    PRNG::Prime_Generator primegen;
    std::random_device rd;
    rng.srand(rd());
    auto start = chrono::steady_clock::now();
    std::cout << rng.random(1) << "\n";
    auto end = chrono::steady_clock::now();
    array<unsigned int,11> sizes = {
        40, 56, 80, 128, 168, 224, 256, 512, 1024, 2048,
        4096
    };
    for (auto a: sizes) {
        start = chrono::steady_clock::now();
            rng.random(a);
        end = chrono::steady_clock::now();
        std::cout << "Elapsed time in nano (" << a << "bits): "
            << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
            << " ns\n";
    }
    
}