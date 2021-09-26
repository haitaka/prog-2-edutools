#include <iostream>

class Meters {
public:
    Meters(unsigned long long int value) : value(value) {}

    // postfix
    Meters operator++(int) {
        Meters old = *this;
        operator++();
        return old;
    }

    // prefix
    Meters & operator++() {
        ++value;
        return *this;
    }

    // conversion
    operator int() const {
        return value;
    }

private:
    unsigned long long int value;
};

Meters operator "" _m (unsigned long long int value) {
    Meters meters(value);
    return meters;
}

Meters operator "" _km (unsigned long long int value) {
    Meters meters(value * 1000);
    return meters;
}

int main() {
    Meters x = 42;
    std::cout << x++ << std::endl;
    std::cout << ++x << std::endl;

    Meters y = 42_km;
    int z = y;
    std::cout << z << std::endl;

    return 0;
}