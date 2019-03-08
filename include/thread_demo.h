#ifndef __THREAD_DEMO__
#define __THREAD_DEMO__

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class ThreadDemo {
public:
    // If following variables are non-static members, they could be initialized like this:
    // threadDemo(const std::string red = std::string("\033[0;31m"),
    //     const std::string green = std::string("\033[0;32m"),
    //     const std::string reset = std::string("\033[0m")) :
    //         red(red), green(green), reset(reset) {}

    void operator() () const {
        std::cout << "Thread demo here:" << std::endl;
        std::cout << "Two threads printing its own id in synchronized manner." << std::endl;

        std::mutex mu;
        std::vector<std::thread> threads(N);
        for(int i = 0; i < N; ++i) {
            threads[i] = std::thread(SpawnThread, std::ref(mu), i);
        }

        for(auto& thread : threads)
            if(thread.joinable())
                thread.join();
    }

private:
    const static int N = 2; // Only const int can be defined at declaration.
    const static std::string red;
    const static std::string green;
    const static std::string reset;

    static void SpawnThread(std::mutex& mu, const int i) {
        for(int j = 0; j < 10; ++j) {
            std::lock_guard<std::mutex> lk(mu);
            if(i % 2) std::cout << red;
            else std::cout << green;
            std::cout << "Thread" << i << ": "  << std::this_thread::get_id() << reset << std::endl;
        }
    }
};

const std::string ThreadDemo::red = "\033[0;31m";   // static member should be defined outside the class
const std::string ThreadDemo::green = "\033[0;32m"; // static member should be defined outside the class
const std::string ThreadDemo::reset = "\033[0m";    // static member should be defined outside the class

#endif // __THREAD_DEMO__
