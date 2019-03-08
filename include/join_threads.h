#ifndef __JOIN_THREADS__
#define __JOIN_THREADS__

#include <thread>
#include <vector>

class JoinThreads {
    std::vector<std::thread>& threads;
public:
    explicit JoinThreads(std::vector<std::thread>& threads_):
        threads(threads_) {}

    ~JoinThreads() {
        for(unsigned long i = 0; i < threads.size(); ++i) {
            if(threads[i].joinable()) threads[i].join();
        }
    }
};

#endif // __JOIN_THREADS__
