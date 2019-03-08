#ifndef __RVALUE_REF_DEMO__
#define __RVALUE_REF_DEMO__

#include <iostream>
#include <string>
#include "util.h"

class RvalueRefDemo {
public:    
    void operator() () const {
        std::cout << "Rvalue reference demo here:" << std::endl;
        std::string s("lvalue string");
        PrintLvalue(s);
        // PrintRvalue(s); // Cannot pass lvalue as rvalue
        PrintRvalue(std::string("rvalue string"));
        PrintLvalue(std::string("rvalue string")); // Pass rvalue as lvalue works only as constant
    }

private:
    void PrintRvalue(std::string&& s) const {
        std::cout << "Expecting rvalue, received " << util::MAGENTA 
            << s << util::RESET << std::endl;
    }

    // C++ does not allow modification to temp object, so it has to be const.
    void PrintLvalue(const std::string& s) const {
        std::cout << "Expecting lvalue, received " << util::MAGENTA 
            << s << util::RESET << std::endl;
    }

};

#endif // __RVALUE_REF_DEMO__
