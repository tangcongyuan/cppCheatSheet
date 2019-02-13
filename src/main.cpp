#include <iostream>
#include <string>
#include "threadDemo.h"

int main(int argc, char** argv) {
    std::cout << "We're going to demo a lot of C++ tricks." << std::endl;

    std::cout << std::string(80, '-') << std::endl;
    threadDemo td;
    td();
    std::cout << std::string(80, '-') << std::endl;

    return 0;
}
