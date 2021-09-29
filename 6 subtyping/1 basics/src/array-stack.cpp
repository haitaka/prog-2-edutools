#include "array-stack.h"

#include <cassert>
#include <algorithm>

ArrayStack::ArrayStack() : ArrayStack(defaultCapacity) {}

ArrayStack::ArrayStack(int capacity)
    : count(0)
    , capacity(capacity)
    , data(new int[capacity]) {}

ArrayStack::ArrayStack(const ArrayStack & orig)
    : count(orig.count)
    , capacity(orig.capacity)
    , data(new int[capacity])
{
    for (int i = 0; i < capacity; ++i) {
        this->data[i] = orig.data[i];
    }
}

ArrayStack::~ArrayStack() {
    delete[] data;
}

void swap(ArrayStack & s1, ArrayStack & s2) {
    using std::swap;
    swap(s1.count, s1.count);
    swap(s1.capacity, s1.capacity);
    swap(s1.data, s1.data);
}

ArrayStack & ArrayStack::operator=(ArrayStack that) {
    swap(*this, that);
    return *this;
}

void ArrayStack::grow() {
    int newCapacity = capacity * 2;
    int * newData = new int[newCapacity];
    for (int i = 0; i < count; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

bool ArrayStack::isEmpty() const {
    return count == 0;
}

void ArrayStack::push(int val) {
    if (count == capacity) {
        grow();
    }
    data[count++] = val;
}

int ArrayStack::pop() {
    int topValue = peek();
    count -= 1;
    return topValue;
}

int ArrayStack::peek() const {
    assert(!isEmpty());
    return data[count - 1];
}

