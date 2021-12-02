#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <mutex>

using namespace std::chrono_literals;

std::mutex storageMutex;
std::vector<int> storage;

void producerBodyMutex() {
    for (auto i = 0; i < 10000; i++) {
        storageMutex.lock();
        storage.push_back(i);
        std::cout << "[Producer] I've just added " << i << std::endl;
        storageMutex.unlock();
        std::this_thread::sleep_for(100ms);
    }
}

void consumerBodyMutex() {
    while (true) {
        storageMutex.lock();
        if (!storage.empty()) {
            auto element = storage[storage.size() - 1];
            std::stringstream ss;
            ss << "[Consumer #" << std::this_thread::get_id() << "] I've just got " << element << std::endl;
            std::cout << ss.str();
            storage.pop_back();
        }
        storageMutex.unlock();

        // also, I'm doing something really heavy here...
        std::this_thread::sleep_for(100ms);
    }
}

void oneProducerThreeConsumersMutex() {
    std::thread producer = std::thread(producerBodyMutex);

    for (int i = 0; i < 3; i++) {
        std::thread(consumerBodyMutex).detach();
    }

    producer.join();
    while (!storage.empty()) {
        std::this_thread::sleep_for(100ms);
    }
}

int main() {
    oneProducerThreeConsumersMutex();
    return 0;
}