#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <mutex>

using namespace std::chrono_literals;

void myDaemonThreadBody() {
    std::stringstream ss;
    ss << "Hello world from daemon thread" << std::endl;
    while (true) {
        std::cout << ss.str();
        std::this_thread::sleep_for(100ms);
    }
}

void myThreadBody(int iterations, int id) {
    std::stringstream ss;
    ss << "Hello world from new thread " << id << std::endl;
    for (int i = 0; i < iterations; i++) {
        std::cout << ss.str();
        std::this_thread::sleep_for(100ms);
    }
}

void justRunThreads() {
    std::vector<std::thread> threads;

    //std::thread d = std::thread(myDaemonThreadBody);
    //d.detach();

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(myThreadBody, 100, i);
    }

    for (int i = 0; i < 2; i++) {
        std::cout << "Hello world from main thread\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (auto &t : threads) {
        t.join();
    }
}

int main() {
    justRunThreads();
    return 0;
}