#include <iostream>

#include "array.h"

void integer() {
    int i = 42;
    i = 23; // possible
}

void integerConst() {
    int const ic = 42;
    const int ci = 42;
    // ic = 23; // impossible
    // ci = 23; // impossible
}

void pointer() {
    int x = 42, y = 37;

    int * ip = &x;
    ip = &y; // possible
    *ip = 23; // possible
}

void constPointer() {
    int x = 42, y = 37;

    int * const ipc = &x;
    // ipc = &y; // impossible
    *ipc = 23; // possible
}

void pointerToConst() {
    int x = 42, y = 37;

    int const * icp = &x;
    const int * cip = &x;
    icp = &y; // possible
    cip = &y; // possible
    // *icp = 23; // impossible
    // *cip = 23; // impossible
}

void constPointerToConst() {
    int x = 42, y = 37;

    int const * const icpc = &x;
    const int * const cipc = &x;
    // icpc = &y; // impossible
    // cipc = &y; // impossible
    // *icpc = 23; // impossible
    // *cipc = 23; // impossible
}

void arrays() {
    int const SIZE = 42;

    Array array(SIZE);
    array.set(0, 37);
    std::cout << array.get(0) << std::endl;

    Array const constArray(SIZE);
    // should not compile: constArray.set(0, 23);
    std::cout << array.get(0) << std::endl;
}

int main() {
    integer();
    integerConst();
    pointer();
    constPointer();
    pointerToConst();
    constPointerToConst();
    arrays();
    return 0;
}
