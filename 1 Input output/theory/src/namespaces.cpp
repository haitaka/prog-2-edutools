#include <iostream>

namespace aaa {
    void foo() {
        std::cout << "aaa::foo" << std::endl;
    }
}

namespace bbb {
    int x = 42;
}

// namespace can be extended from outside
namespace bbb {
    void foo() {
        std::cout << "bbb::foo " << x << std::endl;
    }
}

void foo() {
    std::cout << "foo" << std::endl;
}

int main() {
    aaa::foo();
    bbb::foo();
    foo();
    return 0;
}
