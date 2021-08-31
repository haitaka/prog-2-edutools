#include <iostream>

// TODO seconds and literals
class EvenNumber {
public:
    EvenNumber(int value) : value(value) {
        if (value % 2 != 0) throw std::invalid_argument("Value have to be even");
    }

    // prefix
    EvenNumber & operator++() {
        value += 2;
        return *this;
    }

    // postfix
    EvenNumber operator++(int)
    {
        EvenNumber old = *this;
        operator++();
        return old;
    }

    // conversion
    operator int() {
        return value;
    }

private:
    int value;
};

int main() {
    EvenNumber x(0);
    std::cout << x++ << std::endl;
    std::cout << ++x << std::endl;

    int y = x;

    // will fail
    EvenNumber z = 3;

    return 0;
}