#include <iostream>

void test() {
    int n;
    std::cin >> n;
    int sum = 0;
    while (n > 0) {
        int x;
        std::cin >> x;
        sum += x;
        n -= 1;
    }
    std::cout << sum << std::endl;
}

// do NOT create your own main
