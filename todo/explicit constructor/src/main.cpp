#include <iostream>

class String {
public:
    String(String const & that) {
        *this = that;
    }
    String(char const * c) : data(c) {}
    explicit String(int length) : data(new char[length]) {}

    char const * data;
};

void print(String const & str) {
    std::cout << "Str: " << str.data << "." << std::endl;
}

int main() {
    String s("Hello");

    print(s);
    print("world");

    String s2(42);
    print(s2);
    print(42);

    return 0;
}
