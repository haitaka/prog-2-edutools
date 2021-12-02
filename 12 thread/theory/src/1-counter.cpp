#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

int counter;

void counterBody(int iterations) {
    for (int i = 0; i < iterations; i++) {
        ++counter;
    }
}

void incrementCounter() {
    counter = 0;
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(counterBody, 100000);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << counter << std::endl;
}

int main() {
    incrementCounter();
    return 0;
}