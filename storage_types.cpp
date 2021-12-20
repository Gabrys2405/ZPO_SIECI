//
// Created by majga on 19.12.2021.
//
#include "storage_types.hpp"

Package PackageQueue::pop() {
    throw;
    //return pack();//TODO;
}

void PackageQueue::push(Package&& aPackage) {
    throw;
    //TODO
}
bool PackageQueue::empty() {
    if (size() == 0){
        return true;
    }
    else{
        return false;
    }
}
