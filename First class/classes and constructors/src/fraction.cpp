#include <iostream>
#include <numeric>

class ReducedFraction {
public:
    ReducedFraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
        if (denominator == 0) throw std::invalid_argument("Denominator can't be 0");
        reduce();
    }

    ReducedFraction() : ReducedFraction(1, 2) {}

    ReducedFraction(ReducedFraction const & that) = default;

    int getNumerator() const {
        return this->numerator;
    }

    unsigned int getDenominator() const {
        return denominator;
    }

    friend std::ostream & operator<<(std::ostream & out, ReducedFraction const & f);

private:
    void reduce() {
        int gcd = (int) std::gcd(std::abs(numerator), denominator); // since C++17
        numerator /= gcd;
        denominator /= gcd;
    }

    int numerator;
    unsigned int denominator;
};

std::ostream & operator<<(std::ostream & out, ReducedFraction const & f) {
    out << f.numerator << "/" << f.denominator;
    return out;
}

int main() {
    ReducedFraction f1(3, 2);
    ReducedFraction f2(15, 10);
    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;

    ReducedFraction f3(42, 0);
    return 0;
}
