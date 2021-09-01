#include <iostream>
#include <cassert>

class Array {
public:
    explicit Array(unsigned int length) : length(length), data(new int[length]()) {}

    ~Array() {
        delete[] data;
    }

    Array(Array const & that) : length(that.length), data(new int[that.length]) {
        for (int i = 0; i < length; ++i) {
            data[i] = that.data[i];
        }
    }

    Array & operator=(Array const & that) {
        if (this != &that) {
            length = that.length;
            data = new int[length];
            for (int i = 0; i < length; ++i) {
                data[i] = that.data[i];
            }
        }
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

private:
    unsigned int length;
    int * data;
};

void printElements(Array arr) {
    std::cout << "Array elements:" << std::endl;
    for (int i = 0; i < arr.getLength(); ++i) {
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    Array arr(10);
    for (int i = 0; i < arr.getLength(); ++i) {
        arr[i] = i * 2;
    }

    printElements(arr);
    printElements(arr);

    Array arr2 = arr; // calls copy constructor
    arr2 = arr; // calls assignment operator

    return 0;
}