#include <iostream>

struct Bar {
    int x;

    Bar(Bar const & that) {
        throw 42;
    }

    ~Bar() {
        std::cout << "~Bar(" << x << ")" << std::endl;
    }
};

struct Foo {
    Bar bar;

    explicit Foo(Bar & bar) try : bar(bar) {

    } catch (int x) {

    }
};

class NoSuchDirectory : public std::exception {
public:
    std::string dirName;
    NoSuchDirectory(std::string dirName) : dirName(dirName) {}

    char const * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "No such directory";
    }
};

void foo4() {
    Bar b = {4};
    throw NoSuchDirectory("C:\\foo\\bar");
}

void foo3() {
    Bar b = {3};
    foo4();
}

void foo2() {
    Bar b = {2};
    foo3();
}

void foo1() {
    Bar b = {1};
    foo2();
}

int main() {
    Bar b = {0};

    foo1();

    std::cout << "done" << std::endl;

    return 0;
}