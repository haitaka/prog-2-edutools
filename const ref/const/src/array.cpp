#include <cassert>
#include "array.h"

Array::Array() : Array(DEFAULT_LENGTH) {}

Array::Array(int length)
    : length(length)
    , data(new int[length])
{}

Array::~Array() {
    delete[] data;
}

int Array::get(int index) const {
    assert(0 <= index && index < length);
    return data[index];
}

void Array::set(int index, int value) {
    assert(0 <= index && index < length);
    data[index] = value;
}
