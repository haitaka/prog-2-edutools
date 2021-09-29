#include "stack.h"

#include <iostream>

void Stack::drainAndPrint() {
    while (!isEmpty()) {
        std::cout << pop() << std::endl;
    }
}
