#include <iostream>
#include <cassert>


template<typename T>
T max(T t1, T t2) {
    return t1 > t2 ? t1 : t2;
}

template<>
double max(double t1, double t2) {
    std::cout << "Im double" << std::endl;
    return t1 > t2 ? t1 : t2;
}


int main() {
    std::cout << max(2, 4) << std::endl;
    std::cout << max(1.5, 3.14) << std::endl;
    return 0;
}