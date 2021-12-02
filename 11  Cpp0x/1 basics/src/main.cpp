#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<int> a({1, 2, 3, 4, 5});
    for (auto & i : a) {
        i = 42;
    }
    for (auto i : a) {
        std::cout << i << std::endl;
    }
    return 0;
}