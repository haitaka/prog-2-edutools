#include <iostream>
#include <cassert>

class Array {
public:
    static Array of(int x, int y, int z) {
        Array arr(3);
        arr[0] = x;
        arr[1] = y;
        arr[2] = z;
        return arr;
    }

    explicit Array(unsigned int length) : length(length), data(new int[length]()) {}

    Array(Array const & that) : length(that.length), data(new int[that.length]) {
        for (int i = 0; i < length; ++i) {
            data[i] = that.data[i];
        }
    }

    Array(Array && that) {
        length = std::move(that.length);
        data = std::move(that.data);
        that.data = nullptr;
        that.length = 0;
    }

    ~Array() {
        delete[] data;
    }

    Array & operator=(Array copy) {
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

    Array operator+(Array const & that) const {
        Array sum(length + that.length);
        for (int i = 0; i < length; ++i) {
            sum[i] = (*this)[i];
        }
        for (int i = 0; i < that.length; ++i) {
            sum[length + i] = that[i];
        }
        return sum;
    }

private:
    unsigned int length;
    int * data;
};

int main() {
    Array * c;

    Array d = Array::of(1, 2, 3);

    {
        Array a = Array::of(4, 8, 15);
        Array b = Array::of(16, 23, 42);
        c = new Array(a + b);
    }

    for (int i = 0; i < c->getLength(); ++i) {
        std::cout << (*c)[i] << std::endl;
    }

    return 0;
}
