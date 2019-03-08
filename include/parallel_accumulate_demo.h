#ifndef __PARALLEL_ACCUMULATE_DEMO__
#define __PARALLEL_ACCUMULATE_DEMO__

#include <chrono>
#include <iostream>
#include <vector>
#include "parallel_accumulate.h"

class ParallelAccumulateDemo {
public:
    void operator() () {
        std::cout << "Parallel accumulate demo here:" << std::endl;
        std::cout << "Your computer has " << std::thread::hardware_concurrency() << " cores." << std::endl;

        const unsigned long N = 100000000;
        std::vector<unsigned long> v(N, 0);
        for(unsigned long i = 0; i < N; ++i) v[i] = 1;

        auto start = std::chrono::high_resolution_clock::now();
        unsigned long long result1 = util::ParallelAccumulate(v.begin(), v.end(), 0);
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Parallel accumulation takes " << std::chrono::duration<double, std::milli>(stop - start).count() << " milliseconds." << std::endl;

        start = std::chrono::high_resolution_clock::now();
        unsigned long long result2 = std::accumulate(v.begin(), v.end(), 0);
        stop = std::chrono::high_resolution_clock::now();
        std::cout << "Standard accumulation takes " << std::chrono::duration<double, std::milli>(stop - start).count() << " milliseconds." << std::endl;

        std::cout << "result1 = " << result1 << std::endl;
        std::cout << "result2 = " << result2 << std::endl;
    }
};

#endif // __PARALLEL_ACCUMULATE_DEMO__
