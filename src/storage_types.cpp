//
// Created by majga on 19.12.2021.
//
#include "../include/storage_types.hpp"

Package PackageQueue::pop() {
    if (queueType == PackageQueueType::LIFO && !package_queue.empty()){
//        Package& result = package_queue.front();
        package_queue.pop_front();

    }
    else if(queueType == PackageQueueType::FIFO && !package_queue.empty()) {
        package_queue.pop_back();
    }
    //return result();//TODO;
}

void PackageQueue::push(Package&& aPackage) {
    throw;
    //TODO
}

