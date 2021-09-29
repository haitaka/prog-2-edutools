#include <cassert>
#include <algorithm>
#include "list-stack.h"

ListStack::ListStack() : data(List::nil()) {}

ListStack::ListStack(ListStack const & orig) : data(List::copy(orig.data)) {}

ListStack::~ListStack() {
    delete data;
}

void swap(ListStack & s1, ListStack & s2) {
    using std::swap;
    swap(s1.data, s1.data);
}

ListStack & ListStack::operator=(ListStack that) {
    swap(*this, that);
    return *this;
}

bool ListStack::isEmpty() const {
    return data == List::nil();
}

void ListStack::push(int val) {
    data = new List(val, data);
}

int ListStack::pop() {
    int val = peek();
    data = data->getTail();
    return val;
}

int ListStack::peek() const {
    assert(!isEmpty());
    return data->getHead();
}

