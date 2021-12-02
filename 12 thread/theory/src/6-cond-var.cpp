#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
#include <condition_variable>
#include <mutex>
#include <cassert>

using namespace std::chrono_literals;

std::vector<int> storage;
std::mutex storageMutex;
std::condition_variable storageMutexCondVar;

void producerCondVarBody() {
    for (auto i = 0; i < 1000; i++) {
        {
            std::lock_guard<std::mutex> lock(storageMutex);
            for (auto j = 0; j < 10; j++) {
                storage.push_back(i * 10 + j);
            }
            std::stringstream ss;
            ss << "[Producer] I've just added 10 more elements! It is time to work!" << std::endl;
            std::cout << ss.str();
        }
        storageMutexCondVar.notify_all();
        // sorry, no mo work for some time..
        std::this_thread::sleep_for(100ms);
    }
}

void consumerCondVarBody() {
    while (true) {

        std::unique_lock<std::mutex> lock(storageMutex);

        while (storage.empty()) {
            storageMutexCondVar.wait(lock);
        }

        // storageMutexCondVar.wait(lock, []{return !storage.empty();});

        assert(!storage.empty());
        auto element = storage[storage.size() - 1];
        std::stringstream ss;
        ss << "[Consumer #" << std::this_thread::get_id() << "] I've just got " << element << std::endl;
        std::cout << ss.str();
        storage.pop_back();
        lock.unlock();

        // OK, now we have some really heavy work to be done! see you in 200 ms
        std::this_thread::sleep_for(100ms);
    }
}

void oneProducerSomeConsumersCondVars() {
    std::thread producer = std::thread(producerCondVarBody);

    std::vector<std::thread> consumers;
    for (int i = 0; i < 10; i++) {
        std::thread(consumerCondVarBody).detach();
    }

    producer.join();
    while (!storage.empty()) {
        std::this_thread::sleep_for(100ms);
    }
}

int main() {
    oneProducerSomeConsumersCondVars();
    return 0;
}