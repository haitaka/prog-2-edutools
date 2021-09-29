#include <iostream>
#include "stack.h"
#include "list-stack.h"
#include "array-stack.h"

void drainAndPrint(Stack * stack) {
    // same as
    // stack->drainAndPrint();

    while(!stack->isEmpty()) {
        std::cout << stack->pop() << std::endl;
    }
}

int main() {
    ListStack ls;
    ls.push(4);
    ls.push(8);
    ls.push(15);
    std::cout << "ListStack:" << std::endl;
    drainAndPrint(&ls);
    std::cout << std::endl;

    ArrayStack as;
    as.push(16);
    as.push(23);
    as.push(42);
    std::cout << "ArrayStack:" << std::endl;
    drainAndPrint(&as);
    std::cout << std::endl;

    return 0;
}
