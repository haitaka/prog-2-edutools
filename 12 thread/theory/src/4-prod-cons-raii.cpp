#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <mutex>

using namespace std::chrono_literals;

std::mutex storageMutex;
std::vector<int> storage;

void producerBodyMutexPretty() {
    for (auto i = 0; i < 10000; i++) {
        {
            std::lock_guard<std::mutex> lock(storageMutex);
            storage.push_back(i);
            std::stringstream ss;
            ss << "[Producer] I've just added " << i << std::endl;
            std::cout << ss.str();
        }
        std::this_thread::sleep_for(100ms);
    }
}

void consumerBodyMutexPretty() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(storageMutex);
            if (!storage.empty()) {
                auto element = storage[storage.size() - 1];
                std::stringstream ss;
                ss << "[Consumer #" << std::this_thread::get_id() << "] I've just got " << element << std::endl;
                std::cout << ss.str();
                storage.pop_back();
            }
        }
        std::this_thread::sleep_for(100ms);
    }
}

void oneProducerThreeConsumersMutexPretty() {
    std::thread producer = std::thread(producerBodyMutexPretty);
    for (int i = 0; i < 3; i++) {
        std::thread(consumerBodyMutexPretty).detach();
    }

    producer.join();
    while (!storage.empty()) {
        std::this_thread::sleep_for(100ms);
    }
}

int main() {
    oneProducerThreeConsumersMutexPretty();
    return 0;
}