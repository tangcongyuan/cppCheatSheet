#ifndef __RVALUE_REF__
#define __RVALUE_REF__

class RvalueRef {
public:    
    void operator() () const {
        std::cout << "Rvalue reference demo here." << std::endl;
        std::string s("lvalue string");
        printLvalue(s);
        // printRvalue(s); // Cannot pass lvalue as rvalue
        printRvalue(std::string("rvalue string"));
        printLvalue(std::string("rvalue string")); // Pass rvalue as lvalue works only as constant
    }

private:
    void printRvalue(std::string&& s) const {
        std::cout << "Expecting rvalue, received " << s << std::endl;
    }

    // C++ does not allow modification to temp object, so it has to be const.
    void printLvalue(const std::string& s) const {
        std::cout << "Expecting lvalue, received " << s << std::endl;
    }

};

#endif // __RVALUE_REF__
