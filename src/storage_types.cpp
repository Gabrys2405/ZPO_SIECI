//
// Created by majga on 19.12.2021.
//
#include "../include/storage_types.hpp"

Package PackageQueue::pop() {
    if (_queueType == PackageQueueType::LIFO && !_package_queue.empty()){
//        Package& result = package_queue.front();
        _package_queue.pop_front();

    }
    else if(_queueType == PackageQueueType::FIFO && !_package_queue.empty()) {
        _package_queue.pop_back();
    }
    //return result();//TODO;
}

void PackageQueue::push(Package&& package) {

    _package_queue.emplace_back(std::move(package));
}

