#ifndef __PARALLEL_ACCUMULATE__
#define __PARALLEL_ACCUMULATE__

#include <algorithm>
#include <future>
#include <numeric>
#include <thread>
#include <vector>
#include "join_threads.h"

namespace util {

template<typename Iterator, typename T>
struct AccumulateBlock {
    T operator()(Iterator first, Iterator last) {
        return std::accumulate(first, last, T());
    }
};

template<typename Iterator, typename T>
T ParallelAccumulate(Iterator first, Iterator last, T init) {
    const unsigned long length = std::distance(first, last);

    if(!length) return init;

    const unsigned long min_per_thread = 25;
    const unsigned long max_threads =
        (length + min_per_thread - 1) / min_per_thread;

    const unsigned long hardware_threads = 
        std::thread::hardware_concurrency();

    const unsigned long num_threads = 
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    const unsigned long block_size = length / num_threads;

    std::vector<std::future<T>> futures(num_threads - 1);
    std::vector<std::thread> threads(num_threads - 1);
    JoinThreads joiner(threads);

    Iterator block_start = first;
    for(unsigned long i = 0; i < (num_threads - 1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        std::packaged_task<T(Iterator, Iterator)> task{
            AccumulateBlock<Iterator, T>()};
        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);
        block_start = block_end;
    }
    T last_result = AccumulateBlock<Iterator, T>()(block_start, last);
    T result = init;
    for(unsigned long i = 0; i < (num_threads - 1); ++i) {
        result += futures[i].get();
    }
    result += last_result;
    return result;
}

} // end of namespace util
#endif // __PARALLEL_ACCUMULATE__
