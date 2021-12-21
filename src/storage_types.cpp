//
// Created by majga on 19.12.2021.
//
#include "../include/storage_types.hpp"


Package PackageQueue::pop() {
    // Wyciąganie elementu z kolejki (usuwanie ze zwracaniem)
    Package result;
    switch(get_queue_type()) {

        case PackageQueueType::LIFO :
            result = std::move(_package_queue.back());
            _package_queue.pop_back();
            return result;

        case PackageQueueType::FIFO :
            result = std::move(_package_queue.front());
            _package_queue.pop_front();
            return result;

        default:
            break;

    }
}

void PackageQueue::push(Package&& package) {

    _package_queue.emplace_back(std::move(package));
}

