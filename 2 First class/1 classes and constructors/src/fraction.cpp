#include <iostream>
#include <numeric>

class ReducedFraction {
public:
    ReducedFraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) throw std::invalid_argument("Denominator can't be 0");
        reduce();
    }

    ReducedFraction() : ReducedFraction(1, 2) {}

    int getNumerator() const {
        return this->numerator;
    }

    unsigned int getDenominator() const {
        return denominator;
    }

    void print() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }

private:
    void reduce() {
        int gcd = (int) std::gcd(std::abs(numerator), denominator); // since C++17
        numerator /= gcd;
        denominator /= gcd;
    }

    int numerator;
    unsigned int denominator;
};

int main() {
    ReducedFraction f1(3, 2);
    ReducedFraction f2(15, 10);
    f1.print();
    f2.print();

    ReducedFraction f3(42, 0);
    return 0;
}
