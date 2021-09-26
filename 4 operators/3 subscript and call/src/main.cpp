#include <iostream>
#include <cassert>

class Array {
public:
    explicit Array(unsigned int length) : length(length), data(new int[length]()) {}

    ~Array() {
        delete[] data;
    }

    int & operator[](int index) {
        assert(0 <= index && index < length);
        return data[index];
    }

    int const & operator[](int index) const {
        assert(0 <= index && index < length);
        return data[index];
    }

    int operator()(int id1, int id2, int id3) {
        int val1 = (*this)[id1];
        int val2 = (*this)[id2];
        int val3 = (*this)[id3];
        return val1 + val2 + val3;
    }

private:
    unsigned int const length;
    int * data;
};

void printFirstElement(Array const & arr) {
    std::cout << arr[0] << std::endl;
}

int main() {
    Array const arr(42);

    int x = arr.operator[](0);
    int & ref = x;
    ref = 23;

    arr[0] = 23;

    printFirstElement(arr);

    std::cout << arr(0, 1, 2) << std::endl;

    return 0;
}