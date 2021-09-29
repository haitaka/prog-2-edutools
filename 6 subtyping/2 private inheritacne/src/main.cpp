#include <iostream>
#include <vector>

class StackOnPrivateInh : private std::vector<int> {
public:
    StackOnPrivateInh() : std::vector<int>() {
        top = 0;
    }

    void push(int x) {
        std::vector<int>::resize(top);
        std::vector<int>::at(top++) = x;
    }
    int pop() {
        int topValue = peek();
        --top;
        return topValue;
    }
    int peek() const {
        return std::vector<int>::at(top-1);
    }

    // different from std::vector<int> size
    int size() const {
        return top;
    }

    // reserves memory without affections size etc
    using std::vector<int>::reserve;

private:
    int top;
};

// same as above but without inheritance
class StackOnAggregation {
public:
    StackOnAggregation() : data() {
        top = 0;
    }

    void push(int x) {
        data.resize(top);
        data.at(top++) = x;
    }
    int pop() {
        int topValue = peek();
        --top;
        return topValue;
    }
    int peek() const {
        return data.at(top-1);
    }
    int size() const {
        return top;
    }
    void reserve(int size) {
        data.reserve(size);
    }

private:
    std::vector<int> data;
    int top;
};


int main() {
    StackOnPrivateInh s;
    s.push(4);
    s.push(8);
    s.push(15);

    std::cout << s.pop() << std::endl;
    std::cout << s.pop() << std::endl;
    std::cout << s.pop() << std::endl;

    // however, the following is a compile error
    // std::vector<int> * v = &s;

    // as well as
    // s.at(23) = 42;

    return 0;
}
