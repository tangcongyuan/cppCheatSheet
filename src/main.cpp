#include <iostream>
#include <string>
#include "thread_demo.h"
#include "rvalue_ref_demo.h"
#include "parallel_accumulate_demo.h"

int main(int argc, char** argv) {
    std::cout << "We're going to demo a lot of C++ tricks." << std::endl;

    std::cout << std::string(80, '-') << std::endl;
    ThreadDemo td;
    td();
    std::cout << std::string(80, '-') << std::endl;
    RvalueRefDemo rr;
    rr();
    std::cout << std::string(80, '-') << std::endl;
    ParallelAccumulateDemo pa;
    pa();
    std::cout << std::string(80, '-') << std::endl;

    return 0;
}
