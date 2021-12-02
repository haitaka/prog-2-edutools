#include <thread>
#include <iostream>
#include <vector>
#include <sstream>
#include <mutex>

std::vector<int> storage1;
std::mutex storage1Mutex;

std::vector<int> storage2;
std::mutex storage2Mutex;

void swapElements(std::vector<int>& s1, std::mutex& m1, std::vector<int>& s2, std::mutex& m2, int id) {
    for (int i = 0; i < std::min(s1.size(), s2.size()); i++) {
        m1.lock();
        m2.lock();

        std::swap(s1[i], s2[i]);
        std::cout << "swapped elements at index " << i << " in thread " << id << std::endl;

        m1.unlock();
        m2.unlock();
    }
}

void demoDeadLock() {
    for (int i = 0; i < 100000; i++) {
        storage1.push_back(i*i);
        storage2.push_back(i + i);
    }

    std::thread t1(swapElements, std::ref(storage1), std::ref(storage1Mutex), std::ref(storage2), std::ref(storage2Mutex), 0);
    std::thread t2(swapElements, std::ref(storage2), std::ref(storage2Mutex), std::ref(storage1), std::ref(storage1Mutex), 1);

    t1.join();
    t2.join();
}

void swapElementsNoDeadLocks(std::vector<int>& s1, std::mutex& m1, std::vector<int>& s2, std::mutex& m2, int id) {
    for (int i = 0; i < std::min(s1.size(), s2.size()); i++) {
        std::unique_lock<std::mutex> lock1(m1, std::defer_lock);
        std::unique_lock<std::mutex> lock2(m2, std::defer_lock);
        std::lock(lock1, lock2);

        std::swap(s1[i], s2[i]);
        std::cout << "swapped elements at index " << i << " in thread " << id << std::endl;
    }
}

void demoNoDeadLocks() {
    for (int i = 0; i < 100000; i++) {
        storage1.push_back(i*i);
        storage2.push_back(i + i);
    }

    std::thread t1(swapElementsNoDeadLocks, std::ref(storage1), std::ref(storage1Mutex), std::ref(storage2), std::ref(storage2Mutex), 0);
    std::thread t2(swapElementsNoDeadLocks, std::ref(storage2), std::ref(storage2Mutex), std::ref(storage1), std::ref(storage1Mutex), 1);

    t1.join();
    t2.join();
}

int main() {
    demoDeadLock();
//    demoNoDeadLocks();
    return 0;
}