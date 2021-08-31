#include <sys/resource.h>
#include <iostream>
#include <malloc.h>
#include <glob.h>
#include <cassert>

 // TODO
class Array {
public:
    Array() : Array(DEFAULT_LENGTH) {}

    Array(int length) : length(length), data(new int[length]) {
        std::cout << "Constructed new array with data at " << data << std::endl;
    }

    ~Array() {
        delete[] data;
    }

    int get(int index) {
        assert(0 <= index && index < length);
        return data[index];
    }

    void set(int index, int value) {
        assert(0 <= index && index < length);
        data[index] = value;
    }

private:
    static int const DEFAULT_LENGTH = 1024;

    unsigned int length;
    int * data;
};

int main() {
    int const N = 2 * 1000 * 1000;

    for (int i = 0; i < N; ++i) {
        std::cout << "Iteration " << i << ": ";
        Array array(4096);
        // somehow use the array;
        array.set(0, 42);
    }

    return 0;
}