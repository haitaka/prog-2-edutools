#include <iostream>
#include <cassert>

class Array {
public:
    explicit Array(unsigned int length) : length(length), data(new int[length]()) {
        std::cout << "main constructor" << std::endl;
    }

    Array(Array const & that) : length(that.length), data(new int[that.length]) {
        std::cout << "copy constructor" << std::endl;
        for (int i = 0; i < length; ++i) {
            data[i] = that.data[i];
        }
    }

    ~Array() {
        std::cout << "destructor" << std::endl;
        delete[] data;
    }

    Array & operator=(Array copy) {
        std::cout << "assignment" << std::endl;
        swap(*this, copy);
        return *this;
    }

    int & operator[](int index) {
        assert(0 <= index && index < length);
        return data[index];
    }

    int const & operator[](int index) const {
        assert(0 <= index && index < length);
        return data[index];
    }

    unsigned int getLength() const {
        return length;
    }

    friend void swap(Array & a, Array & b) {
        using std::swap;
        swap(a.length, b.length);
        swap(a.data, b.data);
    }

private:
    unsigned int length;
    int * data;
};

int main() {
    Array y(2);
    y[0] = 42;
    y[1] = 37;

    Array arr(y);
    std::cout << "Array elements:" << std::endl;
    for (int i = 0; i < arr.getLength(); ++i) {
        std::cout << arr[i] << std::endl;
    }


    return 0;
}
