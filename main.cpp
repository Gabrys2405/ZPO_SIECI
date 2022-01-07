//
// Created by majga on 20.12.2021.
//

#include "include/storage_types.hpp"
#include "src/package.cpp"
#include "src/storage_types.cpp"
#include "include/package.hpp"
#include <iostream>

int main() {
    PackageQueue Queue(PackageQueueType::LIFO);
    if (Queue.get_queue_type() == PackageQueueType::LIFO) {
        std::cout << "LIFO" << std::endl;
    }

    Package aPackage;
    std::cout << aPackage.get_id() << std::endl;
    Queue.push(std::move(aPackage));
    Package aPackage1;
    std::cout << aPackage1.get_id() << std::endl;
    Queue.push(std::move(aPackage1));
    Package aPackage2;
    std::cout << aPackage2.get_id() << std::endl;
    Queue.push(std::move(aPackage2));
    Package aPackage3;
    std::cout << aPackage3.get_id() << std::endl;
    Queue.push(std::move(aPackage3));

    std::cout << "\n" << std::endl;

    Package aPack_copy(Queue.pop());
    std::cout << "kopia: " << aPack_copy.get_id() << std::endl;

    std::cout << Queue.pop().get_id() << std::endl;
    std::cout << Queue.pop().get_id() << std::endl;

    Queue.push(std::move(aPack_copy));
    std::cout << "ostatni: " << Queue.pop().get_id() << std::endl;
    std::cout << "\n" << std::endl;

    Package aPackage4;
    std::cout << aPackage4.get_id() << std::endl;
    return 0;
}