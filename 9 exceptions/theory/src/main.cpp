#include <iostream>

class MyException : public std::exception {
private:
    int x;
public:
    MyException(int x) : x(x) {}

    char const * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "division by zero";
    }
};

int myDiv(int x, int y) {
    if (y == 0) throw MyException(x);
    return x / y;
}

struct T {
    int * p;
    T(int x) : p(new int[42]) {
        p[0] = x;
    }
    ~T() {
        std::cout << "T DESTR " << p[0] << std::endl;
        delete[] p;
    }
};

struct S {
    T t1;
    int y;
    T t2;

    S() try : t1(2), y(myDiv(4, 0)), t2(3) {
        std::cout << "foo" << std::endl;
    } catch (...) {
        std::cerr << "!!!" << std::endl;
        throw;
    }

    ~S() {
        std::cout << "S DESTR" << std::endl;
    }
};

int foo(int x, int y) {
    S s;
    return s.y;
}

void bar(int * arr, int size) {
    int t = arr[0];
    for (int i = 0; i < size; ++i) {
        arr[i] = arr[(i+3) % size];
    }
    arr[size - 3] = t;
}

int main() {
    try {
        S s;
        //        int z = foo(1, 0);
        //        std::cout << z << std::endl;
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
        throw;
    } catch (int x) {
        std::cerr << x << std::endl;
    }
    return 0;
}
