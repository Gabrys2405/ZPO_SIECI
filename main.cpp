//
// Created by majga on 20.12.2021.
//

#include "include/storage_types.hpp"
#include "src/package.cpp"
#include "src/storage_types.cpp"
#include "include/package.hpp"

#include <iostream>
int main(){
    Package aPackage;
    std::cout<< aPackage.get_id()<<std::endl;
    Package aPackage1;
    std::cout <<aPackage1.get_id()<<std::endl;
    Package aPackage2;
    std::cout << aPackage2.get_id()<<std::endl;
    Package aPackage3;
    std::cout << aPackage3.get_id()<<std::endl;



    PackageQueue packageQueue(PackageQueueType::FIFO);
    return 0;

}