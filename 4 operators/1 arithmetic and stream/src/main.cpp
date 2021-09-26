#include <iostream>
#include <numeric>

class Complex {
public:
    Complex(int re, int im) : re(re), im(im) {}

    Complex operator+(Complex const & that) const {
        Complex sum(this->re + that.re, this->im + that.im);
        return sum;
    }

    Complex & operator+=(Complex const & that) {
        this->re += that.re;
        this->im += that.im;
        return *this;
    }

    Complex operator+(int integer) const {
        Complex sum(re + integer, im);
        return sum;
    }

    friend Complex operator+(int integer, Complex const & complex);

    bool operator<(Complex const & that) const {
        return re < that.re && im < that.im;
    }

    bool operator>(Complex const & that) const {
        return that < *this;
    }

    bool operator==(Complex const & that) const {
        return re == that.re && im == that.im;
    }

    bool operator!=(Complex const & that) const {
        return !(*this == that);
    }

    // TODO
    // Complex operator-(Complex const & that) const;
    // Complex & operator-=(Complex const & that);
    // Complex operator*(Complex const & that) const;
    // Complex & operator*=(Complex const & that);
    // Complex operator/(Complex const & that) const;
    // Complex & operator/=(Complex const & that);
    // ...

    friend std::ostream & operator<<(std::ostream & out, Complex const & complex);

private:
    int re;
    int im;
};

Complex operator+(int integer, Complex const & complex) {
    Complex sum(complex.re + integer, complex.im);
    return sum;
}

std::ostream & operator<<(std::ostream & out, Complex const & complex) {
    out << complex.re << " + i*" << complex.im;
    return out;
}

int main() {
    Complex one(1, 0);
    Complex i(0, 1);

    Complex x = one + i;
    (std::cout << x) << std::endl;

    x += i;
    x.operator+=(i);
    std::cout << x << std::endl;

    Complex y = 3 + x + i + i + 7;
    std::cout << y << std::endl;

    return 0;
}