#include <cassert>
#include "list.h"

List * List::nil() {
    return nullptr;
}

List * List::copy(List * orig) {
    if (orig == nil()) {
        return nil();
    } else {
        return new List(orig->getHead(), copy(orig->getTail()));
    }
}

List::List(int head, List * tail) : head(head), tail(tail) {}

List::~List() {
    if (tail != nil()) {
        delete tail;
    }
}

int List::operator[](int idx) {
    if (idx == 0) {
        return head;
    } else {
        assert(tail != nil());
        return (*tail)[idx - 1];
    }
}

int List::getHead() const {
    return head;
}

List * List::getTail() {
    return tail;
}
