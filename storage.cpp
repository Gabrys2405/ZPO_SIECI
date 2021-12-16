//
// Created by majga on 15.12.2021.
//


#include "storage.hpp"

pack IPackageQueue::pop() {
    throw;
    //return pack();
}

//int IPackageQueue::get_queue_type() {
  //  return 0;
}

void IPackageStockpile::push() {
    throw;

}

std::size_t IPackageStockpile::size() {
    throw;
}

bool IPackageStockpile::empty() {
    throw;
}

void IPackageStockpile::push(Package &&) {
    throw;
}
