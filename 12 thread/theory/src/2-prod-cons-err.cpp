#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <mutex>

using namespace std::chrono_literals;

std::vector<int> storage;

void producerBody() {
    for (auto i = 0; i < 10000; i++) {
        storage.push_back(i);
        std::stringstream ss;
        ss << "[Producer] I've just added " << i << std::endl;
        std::cout << ss.str();
        std::this_thread::sleep_for(100ms);
    }
}

void consumerBody() {
    while (true) {
        if (!storage.empty()) {
            auto element = storage[storage.size() - 1];
            std::stringstream ss;
            ss << "[Consumer #" << std::this_thread::get_id() << "] I've just got " << element << std::endl;
            std::cout << ss.str();
            storage.pop_back();

            // also, I'm doing something really heavy here...
            std::this_thread::sleep_for(100ms);
        }
    }
}

void oneProducerThreeConsumersDummy() {
    std::thread producer = std::thread(producerBody);

    for (int i = 0; i < 3; i++) {
        std::thread(consumerBody).detach();
    }

    producer.join();
    while (!storage.empty()) {
        std::this_thread::sleep_for(100ms);
    }
}

int main() {
    oneProducerThreeConsumersDummy();
    return 0;
}