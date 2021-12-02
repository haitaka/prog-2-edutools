#include <memory>
#include <iostream>

struct Pair {
    int x,y;
    Pair(int x, int y) : x(x), y(y) {}
    ~Pair() {
        std::cout << "destr(" << x << ", " << y << ")" << std::endl;
    }
};

void bar() {
    std::shared_ptr<Pair> result = std::make_shared<Pair>(23, 42);
    // теперь result владеет новым объектом класса Pair
    std::cout << "ptr counted " << result.use_count() << " times" << std::endl;
    std::shared_ptr<Pair> result2 = result;
    // теперь еще и result2 владеет этим объектом класса Pair
    std::cout << "ptr counted " << result.use_count() << " times" << std::endl;
    result2.reset();
    // result2 перестает владеть объектом класса Pair,
    // но объект не удаляется, т.к. result все еще владеет им
    std::cout << "ptr counted " << result.use_count() << " times" << std::endl;
}

int main() {
    bar();
    return 0;
}