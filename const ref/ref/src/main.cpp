#include <iostream>

void pointer() {
    int x = 42, y = 37;

    int * p = &x;
    std::cout << p << " points to " << *p << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;

    p = &y;
    std::cout << p << " points to " << *p << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;

    *p = 23;
    std::cout << p << " points to " << *p << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;
}

void reference() {
    int x = 42, y = 37;

    int & r = x;
    // no need to use *
    std::cout << "r refers to " << r << " at address " << &r << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;

    // can't reassign
    // r = &y; // impossible
    r = y;
    std::cout << "r refers to " << r << " at address " << &r << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;

    r = 23;
    std::cout << "r refers to " << r << " at address " << &r << std::endl;
    std::cout << "x = " << x << " y = " << y << std::endl;
}

int main() {
    pointer();
    std::cout << std::endl;
    reference();
    return 0;
}